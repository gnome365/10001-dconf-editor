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

[GtkTemplate (ui = "/ca/desrt/dconf-editor/ui/browser-stack.ui")]
class BrowserStack : Grid
{
    [GtkChild] private Stack stack;
    [GtkChild] private RegistryView browse_view;
    [GtkChild] private RegistryInfo properties_view;
    [GtkChild] private RegistrySearch search_results_view;

    public ViewType current_view { get; private set; default = ViewType.FOLDER; }
    private ViewType pre_search_view = ViewType.SEARCH; // means "not in search"

    public bool small_keys_list_rows
    {
        set
        {
            browse_view.small_keys_list_rows = value;
            search_results_view.small_keys_list_rows = value;
        }
    }

    public ModificationsHandler modifications_handler
    {
        set {
            browse_view.modifications_handler = value;
            properties_view.modifications_handler = value;
            search_results_view.modifications_handler = value;
        }
    }

    /*\
    * * Views
    \*/

    public string get_selected_row_name ()
    {
        if (current_view == ViewType.FOLDER)
            return browse_view.get_selected_row_name ();
        if (current_view == ViewType.SEARCH)
            return search_results_view.get_selected_row_name ();
        return "";
    }

    public void prepare_browse_view (GLib.ListStore key_model, bool is_ancestor)
    {
        browse_view.set_key_model (key_model);

        stack.set_transition_type (is_ancestor && pre_search_view == ViewType.SEARCH ? StackTransitionType.CROSSFADE : StackTransitionType.NONE);
        pre_search_view = ViewType.SEARCH;
    }

    public void select_row (string selected, string last_context)
    {
        bool grab_focus = true;     // unused, for now
        if (selected != "")
            browse_view.select_row_named (selected, last_context, grab_focus);
        else
            browse_view.select_first_row (grab_focus);
        properties_view.clean ();
    }

    public void prepare_properties_view (Key key, bool is_parent)
    {
        properties_view.populate_properties_list_box (key);

        stack.set_transition_type (is_parent && pre_search_view == ViewType.SEARCH ? StackTransitionType.CROSSFADE : StackTransitionType.NONE);
        pre_search_view = ViewType.SEARCH;
    }

    public void hide_search_view ()
    {
        if (pre_search_view != ViewType.SEARCH)
        {
            stack.set_transition_type (StackTransitionType.NONE);
            current_view = pre_search_view;
            pre_search_view = ViewType.SEARCH;

            if (current_view == ViewType.FOLDER)
            {
                stack.set_visible_child (browse_view);
                browse_view.focus_selected_row ();
            }
            else if (current_view == ViewType.OBJECT)
                stack.set_visible_child (properties_view);
            else
                assert_not_reached ();
        }
        search_results_view.stop_search ();
    }

    public void set_path (ViewType type, string path)
    {
        if (type == ViewType.FOLDER)
        {
            current_view = type;
            stack.set_visible_child (browse_view);
        }
        else if (type == ViewType.OBJECT)
        {
            current_view = type;
            stack.set_visible_child (properties_view);
        }
        else // (type == ViewType.SEARCH)
        {
            search_results_view.start_search (path);
            if (pre_search_view == ViewType.SEARCH)
            {
                stack.set_transition_type (StackTransitionType.NONE);
                pre_search_view = current_view;

                current_view = type;
                stack.set_visible_child (search_results_view);
            }
        }
    }

    public string? get_copy_text ()
    {
        return ((BrowsableView) stack.get_visible_child ()).get_copy_text ();
    }

    public string? get_copy_path_text ()
    {
        if (current_view == ViewType.SEARCH)
            return search_results_view.get_copy_path_text ();

        warning ("BrowserView get_copy_path_text() called but current view is not search results view.");
        return null;
    }

    public bool show_row_popover ()
    {
        if (current_view == ViewType.FOLDER)
            return browse_view.show_row_popover ();
        if (current_view == ViewType.SEARCH)
            return search_results_view.show_row_popover ();
        return false;
    }

    public void toggle_boolean_key ()
    {
        if (current_view == ViewType.FOLDER)
            browse_view.toggle_boolean_key ();
        else if (current_view == ViewType.SEARCH)
            search_results_view.toggle_boolean_key ();
    }

    public void set_selected_to_default ()
    {
        if (current_view == ViewType.FOLDER)
            browse_view.set_selected_to_default ();
        else if (current_view == ViewType.SEARCH)
            search_results_view.set_selected_to_default ();
    }

    public void discard_row_popover ()
    {
        if (current_view == ViewType.FOLDER)
            browse_view.discard_row_popover ();
        else if (current_view == ViewType.SEARCH)
            search_results_view.discard_row_popover ();
    }

    public void invalidate_popovers ()
    {
        browse_view.invalidate_popovers ();
        search_results_view.invalidate_popovers ();
    }

    /*\
    * * Reload
    \*/

    public void set_search_parameters (string current_path, string [] bookmarks, SortingOptions sorting_options)
    {
        search_results_view.set_search_parameters (current_path, bookmarks, sorting_options);
    }

    public bool check_reload_folder (GLib.ListStore fresh_key_model)
    {
        return browse_view.check_reload (fresh_key_model);
    }

    public bool check_reload_object (Variant properties)
    {
        return properties_view.check_reload (properties);
    }

    /*\
    * * Keyboard calls
    \*/

    public bool return_pressed ()
        requires (current_view == ViewType.SEARCH)
    {
        return search_results_view.return_pressed ();
    }

    public bool up_pressed ()
    {
        if (current_view == ViewType.FOLDER)
            return browse_view.up_or_down_pressed (false);
        if (current_view == ViewType.SEARCH)
            return search_results_view.up_or_down_pressed (false);
        return false;
    }

    public bool down_pressed ()
    {
        if (current_view == ViewType.FOLDER)
            return browse_view.up_or_down_pressed (true);
        if (current_view == ViewType.SEARCH)
            return search_results_view.up_or_down_pressed (true);
        return false;
    }
}

public interface BrowsableView
{
    public abstract string? get_copy_text ();
}
