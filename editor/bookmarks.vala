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
  along with Dconf Editor.  If not, see <https://www.gnu.org/licenses/>.
*/

using Gtk;

[GtkTemplate (ui = "/ca/desrt/dconf-editor/ui/bookmarks.ui")]
private class Bookmarks : MenuButton
{
    [GtkChild] private ListBox bookmarks_list_box;
    [GtkChild] private Popover bookmarks_popover;

    [GtkChild] private Image bookmarks_icon;
    [GtkChild] private Switch bookmarked_switch;

    private string current_path = "/";

    private string schema_id = "ca.desrt.dconf-editor.Bookmarks";   // TODO move in a library
    public string schema_path { private get; internal construct; }
    private GLib.Settings settings;

    construct
    {
        install_action_entries ();

        settings = new GLib.Settings.with_path (schema_id, schema_path);

        ulong bookmarks_changed_handler = settings.changed ["bookmarks"].connect (on_bookmarks_changed);

        update_bookmarks ();
        ulong clicked_handler = clicked.connect (() => { if (active) bookmarked_switch.grab_focus (); });

        destroy.connect (() => {
                settings.disconnect (bookmarks_changed_handler);
                disconnect (clicked_handler);
            });
    }

    private void on_bookmarks_changed ()
    {
        update_bookmarks ();
        update_icon_and_switch ();
    }

    /*\
    * * Public calls
    \*/

    internal void set_path (ViewType type, string path)
    {
        if (type == ViewType.SEARCH)
            return;

        if (current_path != path)
            current_path = path;
        update_icon_and_switch ();
    }

    // for search
    internal string [] get_bookmarks ()
    {
        string [] all_bookmarks = settings.get_strv ("bookmarks");
        string [] unduplicated_bookmarks = {};
        foreach (string bookmark in all_bookmarks)
        {
            if (bookmark in unduplicated_bookmarks)
                continue;
            unduplicated_bookmarks += bookmark;
        }
        return unduplicated_bookmarks;
    }

    // keyboard call
    internal void set_bookmarked (string path, bool new_state)
    {
        if (path == current_path && bookmarked_switch.get_active () == new_state)
            return;

        if (new_state)
            append_bookmark (path);
        else
            remove_bookmark (path);
    }

    internal void update_bookmark_icon (string bookmark, bool bookmark_exists, bool bookmark_has_schema, bool bookmark_is_default)
    {
        bookmarks_list_box.@foreach ((widget) => {
                Bookmark bookmark_row = (Bookmark) (!) widget;

                if (bookmark_row.bookmark_name != bookmark)
                    return; // TODO probably doesn't stop other row to be checked

                StyleContext context = ((!) bookmark_row.get_child ()).get_style_context ();
                context.add_class ("key");
                if (!bookmark_exists)
                {
                    context.add_class ("dconf-key");
                    context.add_class ("erase");
                    return;
                }
                if (!bookmark_has_schema)
                {
                    context.add_class ("dconf-key");
                    return;
                }
                context.add_class ("gsettings-key");
                if (!bookmark_is_default)
                    context.add_class ("edited");
            });
    }

    /*\
    * * Action entries
    \*/

    private void install_action_entries ()
    {
        SimpleActionGroup action_group = new SimpleActionGroup ();
        action_group.add_action_entries (action_entries, this);
        insert_action_group ("bookmarks", action_group);
    }

    private const GLib.ActionEntry [] action_entries =
    {
        {   "bookmark",   bookmark, "s" },
        { "unbookmark", unbookmark, "s" }
    };

    private void bookmark (SimpleAction action, Variant? path_variant)
        requires (path_variant != null)
    {
        bookmarks_popover.closed ();    // if the popover is visible, the size of the listbox could change 1/2

        append_bookmark (((!) path_variant).get_string ());
    }

    private void unbookmark (SimpleAction action, Variant? path_variant)
        requires (path_variant != null)
    {
        bookmarks_popover.closed ();    // if the popover is visible, the size of the listbox could change 2/2

        remove_bookmark (((!) path_variant).get_string ());
    }

    /*\
    * * Bookmarks management
    \*/

    private void update_icon_and_switch ()
    {
        Variant variant = new Variant.string (current_path);
        if (current_path in settings.get_strv ("bookmarks"))
        {
            if (bookmarks_icon.icon_name != "starred-symbolic")
                bookmarks_icon.icon_name = "starred-symbolic";
            update_switch (true);
            bookmarked_switch.set_detailed_action_name ("bookmarks.unbookmark(" + variant.print (false) + ")");
        }
        else
        {
            if (bookmarks_icon.icon_name != "non-starred-symbolic")
                bookmarks_icon.icon_name = "non-starred-symbolic";
            update_switch (false);
            bookmarked_switch.set_detailed_action_name ("bookmarks.bookmark(" + variant.print (false) + ")");
        }
    }
    private void update_switch (bool bookmarked)
    {
        if (bookmarked == bookmarked_switch.active)
            return;
        bookmarked_switch.set_detailed_action_name ("ui.empty('')");
        bookmarked_switch.active = bookmarked;
    }

    private void update_bookmarks ()
    {
        bookmarks_list_box.@foreach ((widget) => widget.destroy ());

        Variant bookmarks_variant = settings.get_value ("bookmarks");
        set_detailed_action_name ("ui.update-bookmarks-icons(" + bookmarks_variant.print (false) + ")");  // TODO disable action on popover closed

        string [] bookmarks = bookmarks_variant.get_strv ();
        string [] unduplicated_bookmarks = new string [0];
        foreach (string bookmark in bookmarks)
        {
            if (bookmark in unduplicated_bookmarks)
                continue;
            unduplicated_bookmarks += bookmark;

            Bookmark bookmark_row = new Bookmark (bookmark);
            if (ModelUtils.is_key_path (bookmark))
            {
                Variant variant = new Variant ("(sq)", bookmark, ModelUtils.undefined_context_id);
                bookmark_row.set_detailed_action_name ("ui.open-object(" + variant.print (true) + ")");    // TODO save context
            }
            else
            {
                Variant variant = new Variant.string (bookmark);
                bookmark_row.set_detailed_action_name ("ui.open-folder(" + variant.print (false) + ")");
            }
            bookmark_row.show ();
            bookmarks_list_box.add (bookmark_row);
        }
        ListBoxRow? first_row = bookmarks_list_box.get_row_at_index (0);
        if (first_row != null)
            bookmarks_list_box.select_row ((!) first_row);
    }

    private void append_bookmark (string path)
    {
        string [] bookmarks = settings.get_strv ("bookmarks");
        if (!(path in bookmarks))
        {
            bookmarks += path;
            settings.set_strv ("bookmarks", bookmarks);
        }
    }

    private void remove_bookmark (string bookmark_name)
    {
        string [] old_bookmarks = settings.get_strv ("bookmarks");
        if (!(bookmark_name in old_bookmarks))
            return;
        string [] new_bookmarks = new string [0];
        foreach (string bookmark in old_bookmarks)
            if (bookmark != bookmark_name && !(bookmark in new_bookmarks))
                new_bookmarks += bookmark;
        settings.set_strv ("bookmarks", new_bookmarks);
    }
}

[GtkTemplate (ui = "/ca/desrt/dconf-editor/ui/bookmark.ui")]
private class Bookmark : ListBoxRow
{
    [GtkChild] private Grid main_grid;
    [GtkChild] private Label bookmark_label;
    [GtkChild] private Button destroy_button;

    public string bookmark_name { get; construct; }

    internal Bookmark (string _bookmark_name)
    {
        Object (bookmark_name: _bookmark_name);
        if (ModelUtils.is_folder_path (bookmark_name))
            main_grid.get_style_context ().add_class ("folder");
        bookmark_label.set_label (bookmark_name);
        Variant variant = new Variant.string (bookmark_name);
        destroy_button.set_detailed_action_name ("bookmarks.unbookmark(" + variant.print (false) + ")");
    }
}
