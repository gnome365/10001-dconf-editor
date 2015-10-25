/*
  This file is part of Dconf Editor

  Dconf Editor is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Dconf Editor is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Dconf Editor.  If not, see <http://www.gnu.org/licenses/>.
*/

using Gtk;

[GtkTemplate (ui = "/ca/desrt/dconf-editor/ui/dconf-editor.ui")]
class DConfWindow : ApplicationWindow
{
    private string current_path = "/";
    private int window_width = 0;
    private int window_height = 0;
    private bool window_is_maximized = false;
    private bool window_is_fullscreen = false;

    private SettingsModel model = new SettingsModel ();
    [GtkChild] private TreeView dir_tree_view;
    [GtkChild] private TreeSelection dir_tree_selection;
    [GtkChild] private ListBox key_list_box;

    private GLib.Settings settings = new GLib.Settings ("ca.desrt.dconf-editor.Settings");
    [GtkChild] private Bookmarks bookmarks_button;

    [GtkChild] private SearchBar search_bar;
    [GtkChild] private SearchEntry search_entry;
    [GtkChild] private Button search_next_button;

    public DConfWindow ()
    {
        set_default_size (settings.get_int ("window-width"), settings.get_int ("window-height"));
        if (settings.get_boolean ("window-is-fullscreen"))
            fullscreen ();
        else if (settings.get_boolean ("window-is-maximized"))
            maximize ();

        search_bar.connect_entry (search_entry);

        dir_tree_view.set_model (model);

        current_path = settings.get_string ("saved-view");
        if (!settings.get_boolean ("restore-view") || current_path == "/" || current_path == "" || !scroll_to_path (current_path))
        {
            TreeIter iter;
            if (model.get_iter_first (out iter))
                dir_tree_selection.select_iter (iter);
        }
    }

    /*\
    * * Window management callbacks
    \*/

    [GtkCallback]
    private void on_show ()
    {
        if (!settings.get_boolean ("show-warning"))
            return;

        Gtk.MessageDialog dialog = new MessageDialog (this, DialogFlags.MODAL, MessageType.INFO, ButtonsType.NONE, _("Thanks for using Dconf Editor for editing your configurations!"));
        dialog.format_secondary_text (_("Don't forget that some option may break applications, so be careful."));
        dialog.add_buttons (_("I'd be careful."), ResponseType.ACCEPT);

        // TODO don't show box if the user explicitely said she wanted to see the dialog next time?
        Box box = (Box) dialog.get_message_area ();
        CheckButton checkbutton = new CheckButton.with_label (_("Show this dialog next time."));
        checkbutton.visible = true;
        checkbutton.active = true;
        checkbutton.margin_top = 5;
        box.add (checkbutton);

        dialog.response.connect (() => { if (!checkbutton.active) settings.set_boolean ("show-warning", false); });
        dialog.run ();
        dialog.destroy ();
    }

    [GtkCallback]
    private bool on_window_state_event (Widget widget, Gdk.EventWindowState event)
    {
        if ((event.changed_mask & Gdk.WindowState.MAXIMIZED) != 0)
            window_is_maximized = (event.new_window_state & Gdk.WindowState.MAXIMIZED) != 0;
        if ((event.changed_mask & Gdk.WindowState.FULLSCREEN) != 0)
            window_is_fullscreen = (event.new_window_state & Gdk.WindowState.FULLSCREEN) != 0;

        return false;
    }

    [GtkCallback]
    private void on_size_allocate (Allocation allocation)
    {
        if (window_is_maximized || window_is_fullscreen)
            return;
        window_width = allocation.width;
        window_height = allocation.height;
    }

    [GtkCallback]
    private void on_destroy ()
    {
        settings.set_string ("saved-view", current_path);
        settings.set_int ("window-width", window_width);
        settings.set_int ("window-height", window_height);
        settings.set_boolean ("window-is-maximized", window_is_maximized);
        settings.set_boolean ("window-is-fullscreen", window_is_fullscreen);
    }

    /*\
    * * Dir TreeView
    \*/

    [GtkCallback]
    private void dir_selected_cb ()
    {
        search_next_button.set_sensitive (true);        // TODO better, or maybe just hide search_bar 1/2

        GLib.ListStore? key_model = null;

        TreeIter iter;
        if (dir_tree_selection.get_selected (null, out iter))
        {
            key_model = model.get_directory (iter).key_model;
            current_path = model.get_directory (iter).full_name;
            bookmarks_button.current_path = current_path;
        }

        key_list_box.bind_model (key_model, new_list_box_row);
    }

    [GtkCallback]
    private bool scroll_to_path (string full_name)
    {
        TreeIter iter;
        if (model.get_iter_first (out iter))
        {
            do
            {
                Directory dir = model.get_directory (iter);

                if (dir.full_name == full_name)
                {
                    select_dir (iter);
                    bookmarks_button.current_path = full_name;
                    return true;
                }
            }
            while (get_next_iter (ref iter));
        }
        MessageDialog dialog = new MessageDialog (this, DialogFlags.MODAL, MessageType.ERROR, ButtonsType.OK, _("Oops! Cannot find something at this path."));
        dialog.run ();
        dialog.destroy ();
        return false;
    }

    /*\
    * * Key ListBox
    \*/

    private Widget new_list_box_row (Object item)
    {
        if (((Key) item).has_schema)
        {
            KeyListBoxRowEditable key_list_box_row = new KeyListBoxRowEditable ((GSettingsKey) item);
            key_list_box_row.button_press_event.connect (on_button_pressed);
            key_list_box_row.show_dialog.connect (() => {
                    KeyEditor key_editor = new KeyEditor ((GSettingsKey) item);
                    key_editor.set_transient_for (this);
                    key_editor.run ();
                });
            return key_list_box_row;
        }
        else
        {
            KeyListBoxRowEditableNoSchema key_list_box_row = new KeyListBoxRowEditableNoSchema ((DConfKey) item);
            key_list_box_row.button_press_event.connect (on_button_pressed);
            key_list_box_row.show_dialog.connect (() => {
                    KeyEditorNoSchema key_editor = new KeyEditorNoSchema ((DConfKey) item);
                    key_editor.set_transient_for (this);
                    key_editor.run ();
                });
            return key_list_box_row;
        }
        // TODO bug: list_box_row is always activated after the dialog destruction if mouse is over at this time
    }

    private bool on_button_pressed (Widget widget, Gdk.EventButton event)
    {
        ListBoxRow list_box_row = (ListBoxRow) ((KeyListBoxRow) widget).get_parent ();
        key_list_box.select_row (list_box_row);
        list_box_row.grab_focus ();
        return false;
    }

    [GtkCallback]
    private void row_activated_cb (ListBoxRow list_box_row)
    {
        search_next_button.set_sensitive (true);        // TODO better, or maybe just hide search_bar 2/2

        ((KeyListBoxRow) list_box_row.get_child ()).show_dialog ();
    }

    /*\
    * * Search box
    \*/

    [GtkCallback]
    private bool on_key_press_event (Widget widget, Gdk.EventKey event)     // TODO better?
    {
        if (Gdk.keyval_name (event.keyval) == "f" && (event.state & Gdk.ModifierType.CONTROL_MASK) != 0)    // TODO better?
        {
            if (bookmarks_button.active)
                bookmarks_button.active = false;
            search_bar.set_search_mode (!search_bar.get_search_mode ());
            return true;
        }

        if (bookmarks_button.active)        // TODO open bug
            return false;

        return search_bar.handle_event (event);
    }

    [GtkCallback]
    private void on_bookmarks_button_clicked ()
    {
        search_bar.set_search_mode (false);
    }

    [GtkCallback]
    private void find_next_cb ()
    {
        if (!search_bar.get_search_mode ())     // TODO better; switches to next list_box_row when keyboard-activating an entry of the popover
            return;

        TreeIter iter;
        int position = 0;
        if (dir_tree_selection.get_selected (null, out iter))
        {
            ListBoxRow? selected_row = (ListBoxRow) key_list_box.get_selected_row ();
            if (selected_row != null)
                position = ((!) selected_row).get_index () + 1;
        }
        else if (!model.get_iter_first (out iter))      // TODO doesn't that reset iter?
            return;     // TODO better

        bool on_first_directory = true;
        do
        {
            Directory dir = model.get_directory (iter);

            if (!on_first_directory && dir.name.index_of (search_entry.text) >= 0)
            {
                select_dir (iter);
                return;
            }
            on_first_directory = false;

            /* Select next key that matches */
            GLib.ListStore key_model = dir.key_model;
            while (position < key_model.get_n_items ())
            {
                Key key = (Key) key_model.get_object (position);
                if (key_matches (key, search_entry.text))
                {
                    select_dir (iter);
                    key_list_box.select_row (key_list_box.get_row_at_index (position));
                    // TODO select key in ListBox
                    return;
                }
                position++;
            }

            position = 0;
        }
        while (get_next_iter (ref iter));

        search_next_button.set_sensitive (false);
    }

    private void select_dir (TreeIter iter)
    {
        dir_tree_view.expand_to_path (model.get_path (iter));
        dir_tree_selection.select_iter (iter);
        dir_tree_view.scroll_to_cell (model.get_path (iter), null, false, 0, 0);
    }

    private bool key_matches (Key key, string text)
    {
        /* Check key name */
        if (key.name.index_of (text) >= 0)
            return true;

        /* Check key schema (description) */
        if (key.has_schema)
        {
            if (((GSettingsKey) key).summary.index_of (text) >= 0)
                return true;
            if (((GSettingsKey) key).description.index_of (text) >= 0)
                return true;
        }

        /* Check key value */
        if (key.value.is_of_type (VariantType.STRING) && key.value.get_string ().index_of (text) >= 0)
            return true;

        return false;
    }

    private bool get_next_iter (ref TreeIter iter)
    {
        /* Search children next */
        if (model.iter_has_child (iter))
        {
            model.iter_nth_child (out iter, iter, 0);
            return true;
        }

        /* Move to the next branch */
        while (!model.iter_next (ref iter))
        {
            /* Otherwise move to the parent and onto the next iter */
            if (!model.iter_parent (out iter, iter))
                return false;
        }

        return true;
    }
}

[GtkTemplate (ui = "/ca/desrt/dconf-editor/ui/key-list-box-row.ui")]
private class KeyListBoxRow : EventBox
{
    [GtkChild] protected Label key_name_label;
    [GtkChild] protected Label key_value_label;
    [GtkChild] protected Label key_info_label;

    public signal void show_dialog ();

    protected ContextPopover? nullable_popover;
    protected virtual bool generate_popover (ContextPopover popover) { return false; }      // no popover should be created

    public override bool button_press_event (Gdk.EventButton event)     // list_box_row selection is done elsewhere
    {
        if (event.button == Gdk.BUTTON_SECONDARY)
        {
            nullable_popover = new ContextPopover ();
            if (!generate_popover ((!) nullable_popover))
                return false;

            ((!) nullable_popover).set_relative_to (this);
            ((!) nullable_popover).position = PositionType.BOTTOM;     // TODO better

            Gdk.Rectangle rect;
            ((!) nullable_popover).get_pointing_to (out rect);
            rect.x = (int) (event.x - this.get_allocated_width () / 2.0);
            ((!) nullable_popover).set_pointing_to (rect);
            ((!) nullable_popover).show ();
        }

        return false;
    }

    protected static string cool_text_value (Key key)    // TODO better
    {
        return Key.cool_text_value_from_variant (key.value, key.type_string);
    }
}

private class KeyListBoxRowEditableNoSchema : KeyListBoxRow
{
    public DConfKey key { get; private set; }

    public KeyListBoxRowEditableNoSchema (DConfKey _key)
    {
        this.key = _key;

        Pango.AttrList attr_list = new Pango.AttrList ();
        attr_list.insert (Pango.attr_weight_new (Pango.Weight.BOLD));
        key_name_label.set_attributes (attr_list);
        key_value_label.set_attributes (attr_list);

        key_name_label.label = key.name;
        key_value_label.label = cool_text_value (key);
        key_info_label.set_markup ("<i>" + _("No Schema Found") + "</i>");

        key.value_changed.connect (() => { key_value_label.label = cool_text_value (key); if (nullable_popover != null) nullable_popover.destroy (); });
    }

    protected override bool generate_popover (ContextPopover popover)
    {
        popover.new_action ("customize", () => { show_dialog (); });
        popover.new_action ("copy", () => {
                Gdk.Display? display = Gdk.Display.get_default ();
                    if (display == null) return;
                Clipboard clipboard = Clipboard.get_default ((!) display);
                string copy = key.full_name + " " + key.value.print (false);
                clipboard.set_text (copy, copy.length);
            });

        if (key.type_string == "b" || key.type_string == "mb")
        {
            popover.new_section ();
            popover.create_buttons_list (key, false);

            popover.value_changed.connect ((bytes) => { nullable_popover.destroy (); key.value = bytes == null ? new Variant.maybe (VariantType.BOOLEAN, null) : new Variant.from_bytes (key.value.get_type (), (!) bytes, true); });
        }
        return true;
    }
}

private class KeyListBoxRowEditable : KeyListBoxRow
{
    public GSettingsKey key { get; private set; }

    private Pango.AttrList attr_list = new Pango.AttrList ();

    public KeyListBoxRowEditable (GSettingsKey _key)
    {
        this.key = _key;

        key_value_label.set_attributes (attr_list);
        update ();      // sets key_name_label attributes and key_value_label label
        key_name_label.label = key.name;
        key_info_label.label = key.summary;

        key.value_changed.connect (() => { update (); if (nullable_popover != null) nullable_popover.destroy (); });
    }

    protected override bool generate_popover (ContextPopover popover)
    {
        popover.new_action ("customize", () => { show_dialog (); });
        popover.new_action ("copy", () => {
                Gdk.Display? display = Gdk.Display.get_default ();
                    if (display == null) return;
                Clipboard clipboard = Clipboard.get_default ((!) display);
                string copy = key.schema_id + " " + key.name + " " + key.value.print (false);
                clipboard.set_text (copy, copy.length);
            });

        if (key.type_string == "b" || key.type_string == "<enum>" || key.type_string == "mb")
        {
            popover.new_section ();
            popover.create_buttons_list (key, true);

            popover.set_to_default.connect (() => { nullable_popover.destroy (); key.set_to_default (); });
            popover.value_changed.connect ((bytes) => { nullable_popover.destroy (); key.value = bytes == null ? new Variant.maybe (VariantType.BOOLEAN, null) : new Variant.from_bytes (key.value.get_type (), (!) bytes, true); });
        }
        else if (key.type_string == "<flags>")
        {
            popover.new_section ();
            if (!key.is_default)
            {
                popover.new_action ("default2", () => { nullable_popover.destroy (); key.set_to_default (); });
                popover.new_section (false);    // ensures a flag called "default2" won't cause problems
            }
            popover.create_flags_list ((GSettingsKey) key);

            popover.value_changed.connect ((bytes) => { key.value = new Variant.from_bytes (VariantType.STRING_ARRAY, (!) bytes, true); });
        }
        else if (!key.is_default)
        {
            popover.new_section ();
            popover.new_action ("default1", () => { key.set_to_default (); });
        }
        return true;
    }

    private void update ()
    {
        attr_list.change (Pango.attr_weight_new (key.is_default ? Pango.Weight.NORMAL : Pango.Weight.BOLD));
        key_name_label.set_attributes (attr_list);
        // TODO key_info_label.set_attributes (attr_list); ?

        key_value_label.label = cool_text_value (key);
    }
}

private class ContextPopover : Popover
{
    private GLib.Menu menu = new GLib.Menu ();
    private GLib.Menu current_section;

    private ActionMap current_group;
    private string current_group_prefix = "";

    // public signals
    public signal void set_to_default ();
    public signal void value_changed (Bytes? bytes);

    public ContextPopover ()
    {
        new_section ();

        bind_model (menu, null);    // TODO menu.freeze() [and sections?], somewhere
    }

    /*\
    * * Simple actions
    \*/

    public delegate void button_action ();
    public void new_action (string action_action, button_action action)
    {
        string text;
        switch (action_action)        // TODO enum
        {
            /* Translators: "open key-editor dialog" action in the right-click menu on the list of keys */
            case "customize":   text = _("Customize…");     break;
            /* Translators: "copy to clipboard" action in the right-click menu on the list of keys */
            case "copy":        text = _("Copy");           break;
            /* Translators: "reset key value" action in the right-click menu on the list of keys */
            case "default1":    text = _("Set to default"); break;
            /* Translators: "reset key value" option of a multi-choice list in the right-click menu on the list of keys */
            case "default2":    text = _("Default value");  break;      // TODO string duplication
            default: assert_not_reached ();
        }

        SimpleAction simple_action = new SimpleAction (action_action, null);
        simple_action.activate.connect (() => { action (); });
        current_group.add_action (simple_action);

        current_section.append (text, current_group_prefix + "." + action_action);
    }

    public void new_section (bool draw_line = true)
    {
        current_group_prefix += "a";
        current_group = new SimpleActionGroup ();
        insert_action_group (current_group_prefix, (SimpleActionGroup) current_group);

        if (!draw_line)
            return;

        current_section = new GLib.Menu ();
        menu.append_section (null, current_section);
    }

    /*\
    * * Flags
    \*/

    public void create_flags_list (GSettingsKey key)
    {
        GLib.Settings settings = new GLib.Settings (key.schema_id);
        string [] active_flags = settings.get_strv (key.name);
        string [] all_flags = key.range_content.get_strv ();
        SimpleAction [] flags_actions = new SimpleAction [0];
        foreach (string flag in all_flags)
        {
            SimpleAction simple_action = new SimpleAction.stateful (flag, null, new Variant.boolean (flag in active_flags));
            current_group.add_action (simple_action);

            current_section.append (flag, current_group_prefix + "." + flag);

            flags_actions += simple_action;

            simple_action.change_state.connect ((gaction, gvariant) => {
                    gaction.set_state (gvariant);

                    string [] new_flags = new string [0];
                    foreach (SimpleAction action in flags_actions)
                        if (action.state.get_boolean ())
                            new_flags += action.name;
                    Variant variant = new Variant.strv (new_flags);
                    value_changed (variant.get_data_as_bytes ());
                });
        }
    }

    /*\
    * * Choices
    \*/

    public void create_buttons_list (Key key, bool nullable)
    {
        const string ACTION_NAME = "reservedactionprefix";

        VariantType original_type = key.value.get_type ();
        VariantType nullable_type = new VariantType.maybe (original_type);
        string nullable_type_string = nullable_type.dup_string ();
        Variant variant = new Variant.maybe (original_type, key.has_schema && ((GSettingsKey) key).is_default ? null : key.value);

        current_group.add_action (new SimpleAction.stateful (ACTION_NAME, nullable_type, variant));

        if (nullable)
            current_section.append (_("Default value"), current_group_prefix + "." + ACTION_NAME + "(@" + nullable_type_string + " nothing)");   // TODO string duplication

        switch (key.type_string)
        {
            case "b":
                current_section.append (Key.cool_boolean_text_value (true), current_group_prefix + "." + ACTION_NAME + "(@mb true)");
                current_section.append (Key.cool_boolean_text_value (false), current_group_prefix + "." + ACTION_NAME + "(@mb false)");
                break;
            case "<enum>":      // defined by the schema
                Variant range = ((GSettingsKey) key).range_content;
                uint size = (uint) range.n_children ();
                if (size == 0)      // TODO special case also 1?
                    assert_not_reached ();
                for (uint index = 0; index < size; index++)
                    current_section.append (range.get_child_value (index).print (false), current_group_prefix + "." + ACTION_NAME + "(@ms '" + range.get_child_value (index).get_string () + "')");        // TODO use int settings.get_enum ()
                break;
            case "mb":
                current_section.append (Key.cool_boolean_text_value (null), current_group_prefix + "." + ACTION_NAME + "(@mmb just nothing)");
                current_section.append (Key.cool_boolean_text_value (true), current_group_prefix + "." + ACTION_NAME + "(@mmb true)");
                current_section.append (Key.cool_boolean_text_value (false), current_group_prefix + "." + ACTION_NAME + "(@mmb false)");
                break;
        }

        ((GLib.ActionGroup) current_group).action_state_changed [ACTION_NAME].connect ((unknown_string, tmp_variant) => {
                Variant? new_variant = tmp_variant.get_maybe ();
                if (new_variant == null)
                    set_to_default ();
                else if (((!) new_variant).get_data () == null)     // TODO better
                    value_changed (null);
                else
                    value_changed (((!) new_variant).get_data_as_bytes ());
            });
    }
}
