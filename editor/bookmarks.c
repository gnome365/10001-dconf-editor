/* bookmarks.c generated by valac 0.38.2.7-b777e, the Vala compiler
 * generated from bookmarks.vala, do not modify */

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

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>


#define TYPE_PATH_ELEMENT (path_element_get_type ())
#define PATH_ELEMENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_PATH_ELEMENT, PathElement))
#define IS_PATH_ELEMENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_PATH_ELEMENT))
#define PATH_ELEMENT_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), TYPE_PATH_ELEMENT, PathElementIface))

typedef struct _PathElement PathElement;
typedef struct _PathElementIface PathElementIface;

#define TYPE_BOOKMARKS (bookmarks_get_type ())
#define BOOKMARKS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_BOOKMARKS, Bookmarks))
#define BOOKMARKS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_BOOKMARKS, BookmarksClass))
#define IS_BOOKMARKS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_BOOKMARKS))
#define IS_BOOKMARKS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_BOOKMARKS))
#define BOOKMARKS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_BOOKMARKS, BookmarksClass))

typedef struct _Bookmarks Bookmarks;
typedef struct _BookmarksClass BookmarksClass;
typedef struct _BookmarksPrivate BookmarksPrivate;
enum  {
	BOOKMARKS_0_PROPERTY,
	BOOKMARKS_SCHEMA_ID_PROPERTY,
	BOOKMARKS_NUM_PROPERTIES
};
static GParamSpec* bookmarks_properties[BOOKMARKS_NUM_PROPERTIES];
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

#define TYPE_BOOKMARK (bookmark_get_type ())
#define BOOKMARK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_BOOKMARK, Bookmark))
#define BOOKMARK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_BOOKMARK, BookmarkClass))
#define IS_BOOKMARK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_BOOKMARK))
#define IS_BOOKMARK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_BOOKMARK))
#define BOOKMARK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_BOOKMARK, BookmarkClass))

typedef struct _Bookmark Bookmark;
typedef struct _BookmarkClass BookmarkClass;
typedef struct _Block9Data Block9Data;
typedef struct _BookmarkPrivate BookmarkPrivate;
typedef struct _Block10Data Block10Data;
enum  {
	BOOKMARK_0_PROPERTY,
	BOOKMARK_BOOKMARK_NAME_PROPERTY,
	BOOKMARK_NUM_PROPERTIES
};
static GParamSpec* bookmark_properties[BOOKMARK_NUM_PROPERTIES];
#define _vala_assert(expr, msg) if G_LIKELY (expr) ; else g_assertion_message_expr (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, msg);
#define _vala_return_if_fail(expr, msg) if G_LIKELY (expr) ; else { g_return_if_fail_warning (G_LOG_DOMAIN, G_STRFUNC, msg); return; }
#define _vala_return_val_if_fail(expr, msg, val) if G_LIKELY (expr) ; else { g_return_if_fail_warning (G_LOG_DOMAIN, G_STRFUNC, msg); return val; }
#define _vala_warn_if_fail(expr, msg) if G_LIKELY (expr) ; else g_warn_message (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC, msg);

struct _PathElementIface {
	GTypeInterface parent_iface;
};

struct _Bookmarks {
	GtkMenuButton parent_instance;
	BookmarksPrivate * priv;
};

struct _BookmarksClass {
	GtkMenuButtonClass parent_class;
};

struct _BookmarksPrivate {
	GtkListBox* bookmarks_list_box;
	GtkPopover* bookmarks_popover;
	GtkImage* bookmarks_icon;
	GtkSwitch* bookmarked_switch;
	gchar* current_path;
	gchar* _schema_id;
	GSettings* settings;
	gulong switch_active_handler;
};

struct _Block9Data {
	int _ref_count_;
	Bookmarks* self;
	gchar* bookmark;
	Bookmark* bookmark_row;
	gulong destroy_button_clicked_handler;
};

struct _Bookmark {
	GtkGrid parent_instance;
	BookmarkPrivate * priv;
	GtkButton* destroy_button;
};

struct _BookmarkClass {
	GtkGridClass parent_class;
};

struct _Block10Data {
	int _ref_count_;
	Bookmarks* self;
	gulong bookmarks_changed_handler;
};

struct _BookmarkPrivate {
	gchar* _bookmark_name;
	GtkLabel* bookmark_label;
};


static gpointer bookmarks_parent_class = NULL;
static PathElementIface * bookmarks_path_element_parent_iface = NULL;
static gpointer bookmark_parent_class = NULL;

GType path_element_get_type (void) G_GNUC_CONST;
GType bookmarks_get_type (void) G_GNUC_CONST;
#define BOOKMARKS_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_BOOKMARKS, BookmarksPrivate))
void bookmarks_set_path (Bookmarks* self, const gchar* path);
static void bookmarks_update_icon_and_switch (Bookmarks* self);
static gboolean _vala_string_array_contains (gchar* * stack, int stack_length, gchar* needle);
static void bookmarks_update_switch (Bookmarks* self, gboolean bookmarked);
static void bookmarks_update_bookmarks (Bookmarks* self);
static void __lambda5_ (Bookmarks* self, GtkWidget* widget);
static void ___lambda5__gtk_callback (GtkWidget* widget, gpointer self);
GType bookmark_get_type (void) G_GNUC_CONST;
static Block9Data* block9_data_ref (Block9Data* _data9_);
static void block9_data_unref (void * _userdata_);
Bookmark* bookmark_new (const gchar* bookmark_name);
Bookmark* bookmark_construct (GType object_type, const gchar* bookmark_name);
static void ____lambda6_ (Block9Data* _data9_);
static void bookmarks_remove_bookmark (Bookmarks* self, const gchar* bookmark_name);
static void _____lambda6__gtk_button_clicked (GtkButton* _sender, gpointer self);
static void ____lambda7_ (Block9Data* _data9_);
static void _____lambda7__gtk_widget_destroy (GtkWidget* _sender, gpointer self);
static void bookmarks_switch_changed_cb (Bookmarks* self);
static void _vala_array_add1 (gchar** * array, int* length, int* size, gchar* value);
void bookmarks_set_bookmarked (Bookmarks* self, gboolean new_state);
static void bookmarks_bookmark_activated_cb (Bookmarks* self, GtkListBoxRow* list_box_row);
const gchar* bookmark_get_bookmark_name (Bookmark* self);
static void _bookmarks_bookmark_activated_cb_gtk_list_box_row_activated (GtkListBox* _sender, GtkListBoxRow* row, gpointer self);
static void _vala_array_add2 (gchar** * array, int* length, int* size, gchar* value);
Bookmarks* bookmarks_new (void);
Bookmarks* bookmarks_construct (GType object_type);
const gchar* bookmarks_get_schema_id (Bookmarks* self);
static void bookmarks_set_schema_id (Bookmarks* self, const gchar* value);
static GObject * bookmarks_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static Block10Data* block10_data_ref (Block10Data* _data10_);
static void block10_data_unref (void * _userdata_);
static void _bookmarks_switch_changed_cb_g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static void _bookmarks___lambda8_ (Bookmarks* self);
static void __bookmarks___lambda8__g_settings_changed (GSettings* _sender, const gchar* key, gpointer self);
static void _bookmarks___lambda9_ (Block10Data* _data10_);
static void __bookmarks___lambda9__gtk_widget_destroy (GtkWidget* _sender, gpointer self);
static void _bookmarks___lambda10_ (Bookmarks* self);
static void __bookmarks___lambda10__gtk_widget_destroy (GtkWidget* _sender, gpointer self);
static void bookmarks_finalize (GObject * obj);
static void _vala_bookmarks_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_bookmarks_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
#define BOOKMARK_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_BOOKMARK, BookmarkPrivate))
static void bookmark_set_bookmark_name (Bookmark* self, const gchar* value);
static GObject * bookmark_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void bookmark_finalize (GObject * obj);
static void _vala_bookmark_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_bookmark_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);


void bookmarks_set_path (Bookmarks* self, const gchar* path) {
	const gchar* _tmp0_;
	const gchar* _tmp1_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (path != NULL);
	_tmp0_ = self->priv->current_path;
	_tmp1_ = path;
	if (g_strcmp0 (_tmp0_, _tmp1_) != 0) {
		const gchar* _tmp2_;
		gchar* _tmp3_;
		_tmp2_ = path;
		_tmp3_ = g_strdup (_tmp2_);
		_g_free0 (self->priv->current_path);
		self->priv->current_path = _tmp3_;
	}
	bookmarks_update_icon_and_switch (self);
}


static gboolean _vala_string_array_contains (gchar* * stack, int stack_length, gchar* needle) {
	int i;
	for (i = 0; i < stack_length; i++) {
		if (g_strcmp0 (stack[i], needle) == 0) {
			return TRUE;
		}
	}
	return FALSE;
}


static void bookmarks_update_icon_and_switch (Bookmarks* self) {
	const gchar* _tmp0_;
	GSettings* _tmp1_;
	gchar** _tmp2_;
	gchar** _tmp3_;
	gchar** _tmp4_;
	gint _tmp4__length1;
	gboolean _tmp5_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->current_path;
	_tmp1_ = self->priv->settings;
	_tmp3_ = _tmp2_ = g_settings_get_strv (_tmp1_, "bookmarks");
	_tmp4_ = _tmp3_;
	_tmp4__length1 = _vala_array_length (_tmp2_);
	_tmp5_ = _vala_string_array_contains (_tmp4_, _vala_array_length (_tmp2_), _tmp0_);
	_tmp4_ = (_vala_array_free (_tmp4_, _tmp4__length1, (GDestroyNotify) g_free), NULL);
	if (_tmp5_) {
		GtkImage* _tmp6_;
		gchar* _tmp7_;
		gchar* _tmp8_;
		gchar* _tmp9_;
		gboolean _tmp10_;
		_tmp6_ = self->priv->bookmarks_icon;
		g_object_get (_tmp6_, "icon-name", &_tmp7_, NULL);
		_tmp8_ = _tmp7_;
		_tmp9_ = _tmp8_;
		_tmp10_ = g_strcmp0 (_tmp9_, "starred-symbolic") != 0;
		_g_free0 (_tmp9_);
		if (_tmp10_) {
			GtkImage* _tmp11_;
			_tmp11_ = self->priv->bookmarks_icon;
			g_object_set (_tmp11_, "icon-name", "starred-symbolic", NULL);
		}
		bookmarks_update_switch (self, TRUE);
	} else {
		GtkImage* _tmp12_;
		gchar* _tmp13_;
		gchar* _tmp14_;
		gchar* _tmp15_;
		gboolean _tmp16_;
		_tmp12_ = self->priv->bookmarks_icon;
		g_object_get (_tmp12_, "icon-name", &_tmp13_, NULL);
		_tmp14_ = _tmp13_;
		_tmp15_ = _tmp14_;
		_tmp16_ = g_strcmp0 (_tmp15_, "non-starred-symbolic") != 0;
		_g_free0 (_tmp15_);
		if (_tmp16_) {
			GtkImage* _tmp17_;
			_tmp17_ = self->priv->bookmarks_icon;
			g_object_set (_tmp17_, "icon-name", "non-starred-symbolic", NULL);
		}
		bookmarks_update_switch (self, FALSE);
	}
}


static void bookmarks_update_switch (Bookmarks* self, gboolean bookmarked) {
	gulong _tmp0_;
	gboolean _tmp1_;
	GtkSwitch* _tmp2_;
	gboolean _tmp3_;
	gboolean _tmp4_;
	GtkSwitch* _tmp5_;
	gulong _tmp6_;
	GtkSwitch* _tmp7_;
	gboolean _tmp8_;
	GtkSwitch* _tmp9_;
	gulong _tmp10_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->switch_active_handler;
	_vala_return_if_fail (_tmp0_ != ((gulong) 0), "switch_active_handler != 0");
	_tmp1_ = bookmarked;
	_tmp2_ = self->priv->bookmarked_switch;
	_tmp3_ = gtk_switch_get_active (_tmp2_);
	_tmp4_ = _tmp3_;
	if (_tmp1_ == _tmp4_) {
		return;
	}
	_tmp5_ = self->priv->bookmarked_switch;
	_tmp6_ = self->priv->switch_active_handler;
	g_signal_handler_block (_tmp5_, _tmp6_);
	_tmp7_ = self->priv->bookmarked_switch;
	_tmp8_ = bookmarked;
	gtk_switch_set_active (_tmp7_, _tmp8_);
	_tmp9_ = self->priv->bookmarked_switch;
	_tmp10_ = self->priv->switch_active_handler;
	g_signal_handler_unblock (_tmp9_, _tmp10_);
}


static void __lambda5_ (Bookmarks* self, GtkWidget* widget) {
	GtkWidget* _tmp0_;
	g_return_if_fail (widget != NULL);
	_tmp0_ = widget;
	gtk_widget_destroy (_tmp0_);
}


static void ___lambda5__gtk_callback (GtkWidget* widget, gpointer self) {
	__lambda5_ ((Bookmarks*) self, widget);
}


static Block9Data* block9_data_ref (Block9Data* _data9_) {
	g_atomic_int_inc (&_data9_->_ref_count_);
	return _data9_;
}


static void block9_data_unref (void * _userdata_) {
	Block9Data* _data9_;
	_data9_ = (Block9Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data9_->_ref_count_)) {
		Bookmarks* self;
		self = _data9_->self;
		_g_object_unref0 (_data9_->bookmark_row);
		_g_free0 (_data9_->bookmark);
		_g_object_unref0 (self);
		g_slice_free (Block9Data, _data9_);
	}
}


static void ____lambda6_ (Block9Data* _data9_) {
	Bookmarks* self;
	const gchar* _tmp0_;
	self = _data9_->self;
	_tmp0_ = _data9_->bookmark;
	bookmarks_remove_bookmark (self, _tmp0_);
}


static void _____lambda6__gtk_button_clicked (GtkButton* _sender, gpointer self) {
	____lambda6_ (self);
}


static void ____lambda7_ (Block9Data* _data9_) {
	Bookmarks* self;
	Bookmark* _tmp0_;
	GtkButton* _tmp1_;
	gulong _tmp2_;
	self = _data9_->self;
	_tmp0_ = _data9_->bookmark_row;
	_tmp1_ = _tmp0_->destroy_button;
	_tmp2_ = _data9_->destroy_button_clicked_handler;
	g_signal_handler_disconnect ((GObject*) _tmp1_, _tmp2_);
}


static void _____lambda7__gtk_widget_destroy (GtkWidget* _sender, gpointer self) {
	____lambda7_ (self);
}


static void bookmarks_update_bookmarks (Bookmarks* self) {
	GtkListBox* _tmp0_;
	gchar** bookmarks = NULL;
	GSettings* _tmp1_;
	gchar** _tmp2_;
	gchar** _tmp3_;
	gint bookmarks_length1;
	gint _bookmarks_size_;
	gchar** _tmp4_;
	gint _tmp4__length1;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->bookmarks_list_box;
	gtk_container_foreach ((GtkContainer*) _tmp0_, ___lambda5__gtk_callback, self);
	_tmp1_ = self->priv->settings;
	_tmp3_ = _tmp2_ = g_settings_get_strv (_tmp1_, "bookmarks");
	bookmarks = _tmp3_;
	bookmarks_length1 = _vala_array_length (_tmp2_);
	_bookmarks_size_ = bookmarks_length1;
	_tmp4_ = bookmarks;
	_tmp4__length1 = bookmarks_length1;
	{
		gchar** bookmark_collection = NULL;
		gint bookmark_collection_length1 = 0;
		gint _bookmark_collection_size_ = 0;
		gint bookmark_it = 0;
		bookmark_collection = _tmp4_;
		bookmark_collection_length1 = _tmp4__length1;
		for (bookmark_it = 0; bookmark_it < _tmp4__length1; bookmark_it = bookmark_it + 1) {
			gchar* _tmp5_;
			gchar* bookmark = NULL;
			_tmp5_ = g_strdup (bookmark_collection[bookmark_it]);
			bookmark = _tmp5_;
			{
				Block9Data* _data9_;
				const gchar* _tmp6_;
				Bookmark* _tmp7_;
				Bookmark* _tmp8_;
				GtkButton* _tmp9_;
				gulong _tmp10_;
				Bookmark* _tmp11_;
				GtkButton* _tmp12_;
				Bookmark* _tmp13_;
				GtkListBox* _tmp14_;
				Bookmark* _tmp15_;
				_data9_ = g_slice_new0 (Block9Data);
				_data9_->_ref_count_ = 1;
				_data9_->self = g_object_ref (self);
				_data9_->bookmark = bookmark;
				_tmp6_ = _data9_->bookmark;
				_tmp7_ = bookmark_new (_tmp6_);
				g_object_ref_sink (_tmp7_);
				_data9_->bookmark_row = _tmp7_;
				_tmp8_ = _data9_->bookmark_row;
				_tmp9_ = _tmp8_->destroy_button;
				_tmp10_ = g_signal_connect_data (_tmp9_, "clicked", (GCallback) _____lambda6__gtk_button_clicked, block9_data_ref (_data9_), (GClosureNotify) block9_data_unref, 0);
				_data9_->destroy_button_clicked_handler = _tmp10_;
				_tmp11_ = _data9_->bookmark_row;
				_tmp12_ = _tmp11_->destroy_button;
				g_signal_connect_data ((GtkWidget*) _tmp12_, "destroy", (GCallback) _____lambda7__gtk_widget_destroy, block9_data_ref (_data9_), (GClosureNotify) block9_data_unref, 0);
				_tmp13_ = _data9_->bookmark_row;
				gtk_widget_show ((GtkWidget*) _tmp13_);
				_tmp14_ = self->priv->bookmarks_list_box;
				_tmp15_ = _data9_->bookmark_row;
				gtk_container_add ((GtkContainer*) _tmp14_, (GtkWidget*) _tmp15_);
				block9_data_unref (_data9_);
				_data9_ = NULL;
			}
		}
	}
	bookmarks = (_vala_array_free (bookmarks, bookmarks_length1, (GDestroyNotify) g_free), NULL);
}


static void _vala_array_add1 (gchar** * array, int* length, int* size, gchar* value) {
	if ((*length) == (*size)) {
		*size = (*size) ? (2 * (*size)) : 4;
		*array = g_renew (gchar*, *array, (*size) + 1);
	}
	(*array)[(*length)++] = value;
	(*array)[*length] = NULL;
}


static void bookmarks_switch_changed_cb (Bookmarks* self) {
	GtkPopover* _tmp0_;
	gchar** bookmarks = NULL;
	GSettings* _tmp1_;
	gchar** _tmp2_;
	gchar** _tmp3_;
	gint bookmarks_length1;
	gint _bookmarks_size_;
	GtkSwitch* _tmp4_;
	gboolean _tmp5_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->bookmarks_popover;
	g_signal_emit_by_name (_tmp0_, "closed");
	_tmp1_ = self->priv->settings;
	_tmp3_ = _tmp2_ = g_settings_get_strv (_tmp1_, "bookmarks");
	bookmarks = _tmp3_;
	bookmarks_length1 = _vala_array_length (_tmp2_);
	_bookmarks_size_ = bookmarks_length1;
	_tmp4_ = self->priv->bookmarked_switch;
	_tmp5_ = gtk_switch_get_active (_tmp4_);
	if (!_tmp5_) {
		const gchar* _tmp6_;
		_tmp6_ = self->priv->current_path;
		bookmarks_remove_bookmark (self, _tmp6_);
	} else {
		const gchar* _tmp7_;
		gchar** _tmp8_;
		gint _tmp8__length1;
		_tmp7_ = self->priv->current_path;
		_tmp8_ = bookmarks;
		_tmp8__length1 = bookmarks_length1;
		if (!_vala_string_array_contains (_tmp8_, _tmp8__length1, _tmp7_)) {
			gchar** _tmp9_;
			gint _tmp9__length1;
			const gchar* _tmp10_;
			gchar* _tmp11_;
			GSettings* _tmp12_;
			gchar** _tmp13_;
			gint _tmp13__length1;
			_tmp9_ = bookmarks;
			_tmp9__length1 = bookmarks_length1;
			_tmp10_ = self->priv->current_path;
			_tmp11_ = g_strdup (_tmp10_);
			_vala_array_add1 (&bookmarks, &bookmarks_length1, &_bookmarks_size_, _tmp11_);
			_tmp12_ = self->priv->settings;
			_tmp13_ = bookmarks;
			_tmp13__length1 = bookmarks_length1;
			g_settings_set_strv (_tmp12_, "bookmarks", _tmp13_);
		}
	}
	bookmarks = (_vala_array_free (bookmarks, bookmarks_length1, (GDestroyNotify) g_free), NULL);
}


void bookmarks_set_bookmarked (Bookmarks* self, gboolean new_state) {
	GtkSwitch* _tmp0_;
	gboolean _tmp1_;
	gboolean _tmp2_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->bookmarked_switch;
	_tmp1_ = gtk_switch_get_active (_tmp0_);
	_tmp2_ = new_state;
	if (_tmp1_ != _tmp2_) {
		GtkSwitch* _tmp3_;
		gboolean _tmp4_;
		_tmp3_ = self->priv->bookmarked_switch;
		_tmp4_ = new_state;
		gtk_switch_set_active (_tmp3_, _tmp4_);
	}
}


static void bookmarks_bookmark_activated_cb (Bookmarks* self, GtkListBoxRow* list_box_row) {
	GtkPopover* _tmp0_;
	gchar* bookmark = NULL;
	GtkListBoxRow* _tmp1_;
	GtkWidget* _tmp2_;
	const gchar* _tmp3_;
	const gchar* _tmp4_;
	gchar* _tmp5_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (list_box_row != NULL);
	_tmp0_ = self->priv->bookmarks_popover;
	g_signal_emit_by_name (_tmp0_, "closed");
	_tmp1_ = list_box_row;
	_tmp2_ = gtk_bin_get_child ((GtkBin*) _tmp1_);
	_tmp3_ = bookmark_get_bookmark_name (G_TYPE_CHECK_INSTANCE_CAST (_tmp2_, TYPE_BOOKMARK, Bookmark));
	_tmp4_ = _tmp3_;
	_tmp5_ = g_strdup (_tmp4_);
	bookmark = _tmp5_;
	g_signal_emit_by_name ((PathElement*) self, "request-path", bookmark);
	_g_free0 (bookmark);
}


static void _bookmarks_bookmark_activated_cb_gtk_list_box_row_activated (GtkListBox* _sender, GtkListBoxRow* row, gpointer self) {
	bookmarks_bookmark_activated_cb ((Bookmarks*) self, row);
}


static void _vala_array_add2 (gchar** * array, int* length, int* size, gchar* value) {
	if ((*length) == (*size)) {
		*size = (*size) ? (2 * (*size)) : 4;
		*array = g_renew (gchar*, *array, (*size) + 1);
	}
	(*array)[(*length)++] = value;
	(*array)[*length] = NULL;
}


static void bookmarks_remove_bookmark (Bookmarks* self, const gchar* bookmark_name) {
	GtkPopover* _tmp0_;
	gchar** old_bookmarks = NULL;
	GSettings* _tmp1_;
	gchar** _tmp2_;
	gchar** _tmp3_;
	gint old_bookmarks_length1;
	gint _old_bookmarks_size_;
	const gchar* _tmp4_;
	gchar** _tmp5_;
	gint _tmp5__length1;
	gchar** new_bookmarks = NULL;
	gchar** _tmp6_;
	gint new_bookmarks_length1;
	gint _new_bookmarks_size_;
	gchar** _tmp7_;
	gint _tmp7__length1;
	GSettings* _tmp14_;
	gchar** _tmp15_;
	gint _tmp15__length1;
	g_return_if_fail (self != NULL);
	g_return_if_fail (bookmark_name != NULL);
	_tmp0_ = self->priv->bookmarks_popover;
	g_signal_emit_by_name (_tmp0_, "closed");
	_tmp1_ = self->priv->settings;
	_tmp3_ = _tmp2_ = g_settings_get_strv (_tmp1_, "bookmarks");
	old_bookmarks = _tmp3_;
	old_bookmarks_length1 = _vala_array_length (_tmp2_);
	_old_bookmarks_size_ = old_bookmarks_length1;
	_tmp4_ = bookmark_name;
	_tmp5_ = old_bookmarks;
	_tmp5__length1 = old_bookmarks_length1;
	if (!_vala_string_array_contains (_tmp5_, _tmp5__length1, _tmp4_)) {
		old_bookmarks = (_vala_array_free (old_bookmarks, old_bookmarks_length1, (GDestroyNotify) g_free), NULL);
		return;
	}
	_tmp6_ = g_new0 (gchar*, 0 + 1);
	new_bookmarks = _tmp6_;
	new_bookmarks_length1 = 0;
	_new_bookmarks_size_ = new_bookmarks_length1;
	_tmp7_ = old_bookmarks;
	_tmp7__length1 = old_bookmarks_length1;
	{
		gchar** bookmark_collection = NULL;
		gint bookmark_collection_length1 = 0;
		gint _bookmark_collection_size_ = 0;
		gint bookmark_it = 0;
		bookmark_collection = _tmp7_;
		bookmark_collection_length1 = _tmp7__length1;
		for (bookmark_it = 0; bookmark_it < _tmp7__length1; bookmark_it = bookmark_it + 1) {
			gchar* _tmp8_;
			gchar* bookmark = NULL;
			_tmp8_ = g_strdup (bookmark_collection[bookmark_it]);
			bookmark = _tmp8_;
			{
				const gchar* _tmp9_;
				const gchar* _tmp10_;
				_tmp9_ = bookmark;
				_tmp10_ = bookmark_name;
				if (g_strcmp0 (_tmp9_, _tmp10_) != 0) {
					gchar** _tmp11_;
					gint _tmp11__length1;
					const gchar* _tmp12_;
					gchar* _tmp13_;
					_tmp11_ = new_bookmarks;
					_tmp11__length1 = new_bookmarks_length1;
					_tmp12_ = bookmark;
					_tmp13_ = g_strdup (_tmp12_);
					_vala_array_add2 (&new_bookmarks, &new_bookmarks_length1, &_new_bookmarks_size_, _tmp13_);
				}
				_g_free0 (bookmark);
			}
		}
	}
	_tmp14_ = self->priv->settings;
	_tmp15_ = new_bookmarks;
	_tmp15__length1 = new_bookmarks_length1;
	g_settings_set_strv (_tmp14_, "bookmarks", _tmp15_);
	new_bookmarks = (_vala_array_free (new_bookmarks, new_bookmarks_length1, (GDestroyNotify) g_free), NULL);
	old_bookmarks = (_vala_array_free (old_bookmarks, old_bookmarks_length1, (GDestroyNotify) g_free), NULL);
}


Bookmarks* bookmarks_construct (GType object_type) {
	Bookmarks * self = NULL;
	self = (Bookmarks*) g_object_new (object_type, NULL);
	return self;
}


Bookmarks* bookmarks_new (void) {
	return bookmarks_construct (TYPE_BOOKMARKS);
}


const gchar* bookmarks_get_schema_id (Bookmarks* self) {
	const gchar* result;
	const gchar* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_schema_id;
	result = _tmp0_;
	return result;
}


static void bookmarks_set_schema_id (Bookmarks* self, const gchar* value) {
	g_return_if_fail (self != NULL);
	if (g_strcmp0 (value, bookmarks_get_schema_id (self)) != 0) {
		const gchar* _tmp0_;
		gchar* _tmp1_;
		_tmp0_ = value;
		_tmp1_ = g_strdup (_tmp0_);
		_g_free0 (self->priv->_schema_id);
		self->priv->_schema_id = _tmp1_;
		g_object_notify_by_pspec ((GObject *) self, bookmarks_properties[BOOKMARKS_SCHEMA_ID_PROPERTY]);
	}
}


static Block10Data* block10_data_ref (Block10Data* _data10_) {
	g_atomic_int_inc (&_data10_->_ref_count_);
	return _data10_;
}


static void block10_data_unref (void * _userdata_) {
	Block10Data* _data10_;
	_data10_ = (Block10Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data10_->_ref_count_)) {
		Bookmarks* self;
		self = _data10_->self;
		_g_object_unref0 (self);
		g_slice_free (Block10Data, _data10_);
	}
}


static void _bookmarks_switch_changed_cb_g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	bookmarks_switch_changed_cb ((Bookmarks*) self);
}


static void _bookmarks___lambda8_ (Bookmarks* self) {
	bookmarks_update_bookmarks (self);
	bookmarks_update_icon_and_switch (self);
}


static void __bookmarks___lambda8__g_settings_changed (GSettings* _sender, const gchar* key, gpointer self) {
	_bookmarks___lambda8_ ((Bookmarks*) self);
}


static void _bookmarks___lambda9_ (Block10Data* _data10_) {
	Bookmarks* self;
	GSettings* _tmp0_;
	gulong _tmp1_;
	self = _data10_->self;
	_tmp0_ = self->priv->settings;
	_tmp1_ = _data10_->bookmarks_changed_handler;
	g_signal_handler_disconnect ((GObject*) _tmp0_, _tmp1_);
}


static void __bookmarks___lambda9__gtk_widget_destroy (GtkWidget* _sender, gpointer self) {
	_bookmarks___lambda9_ (self);
}


static void _bookmarks___lambda10_ (Bookmarks* self) {
	GtkSwitch* _tmp0_;
	gulong _tmp1_;
	_tmp0_ = self->priv->bookmarked_switch;
	_tmp1_ = self->priv->switch_active_handler;
	g_signal_handler_disconnect ((GObject*) _tmp0_, _tmp1_);
}


static void __bookmarks___lambda10__gtk_widget_destroy (GtkWidget* _sender, gpointer self) {
	_bookmarks___lambda10_ ((Bookmarks*) self);
}


static GObject * bookmarks_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	Bookmarks * self;
	Block10Data* _data10_;
	const gchar* _tmp0_;
	GSettings* _tmp1_;
	GtkSwitch* _tmp2_;
	gulong _tmp3_;
	GSettings* _tmp4_;
	gulong _tmp5_;
	GtkSwitch* _tmp6_;
	GtkSwitch* _tmp7_;
	parent_class = G_OBJECT_CLASS (bookmarks_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_BOOKMARKS, Bookmarks);
	_data10_ = g_slice_new0 (Block10Data);
	_data10_->_ref_count_ = 1;
	_data10_->self = g_object_ref (self);
	_tmp0_ = self->priv->_schema_id;
	_tmp1_ = g_settings_new (_tmp0_);
	_g_object_unref0 (self->priv->settings);
	self->priv->settings = _tmp1_;
	_tmp2_ = self->priv->bookmarked_switch;
	_tmp3_ = g_signal_connect_object ((GObject*) _tmp2_, "notify::active", (GCallback) _bookmarks_switch_changed_cb_g_object_notify, self, 0);
	self->priv->switch_active_handler = _tmp3_;
	_tmp4_ = self->priv->settings;
	_tmp5_ = g_signal_connect_object (_tmp4_, "changed::bookmarks", (GCallback) __bookmarks___lambda8__g_settings_changed, self, 0);
	_data10_->bookmarks_changed_handler = _tmp5_;
	bookmarks_update_bookmarks (self);
	_tmp6_ = self->priv->bookmarked_switch;
	gtk_widget_grab_focus ((GtkWidget*) _tmp6_);
	g_signal_connect_data ((GtkWidget*) self, "destroy", (GCallback) __bookmarks___lambda9__gtk_widget_destroy, block10_data_ref (_data10_), (GClosureNotify) block10_data_unref, 0);
	_tmp7_ = self->priv->bookmarked_switch;
	g_signal_connect_object ((GtkWidget*) _tmp7_, "destroy", (GCallback) __bookmarks___lambda10__gtk_widget_destroy, self, 0);
	block10_data_unref (_data10_);
	_data10_ = NULL;
	return obj;
}


static void bookmarks_class_init (BookmarksClass * klass) {
	gint Bookmarks_private_offset;
	bookmarks_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (BookmarksPrivate));
	G_OBJECT_CLASS (klass)->get_property = _vala_bookmarks_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_bookmarks_set_property;
	G_OBJECT_CLASS (klass)->constructor = bookmarks_constructor;
	G_OBJECT_CLASS (klass)->finalize = bookmarks_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), BOOKMARKS_SCHEMA_ID_PROPERTY, bookmarks_properties[BOOKMARKS_SCHEMA_ID_PROPERTY] = g_param_spec_string ("schema-id", "schema-id", "schema-id", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	Bookmarks_private_offset = g_type_class_get_instance_private_offset (klass);
	gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass), "/ca/desrt/dconf-editor/ui/bookmarks.ui");
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "bookmarks_list_box", FALSE, Bookmarks_private_offset + G_STRUCT_OFFSET (BookmarksPrivate, bookmarks_list_box));
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "bookmarks_popover", FALSE, Bookmarks_private_offset + G_STRUCT_OFFSET (BookmarksPrivate, bookmarks_popover));
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "bookmarks_icon", FALSE, Bookmarks_private_offset + G_STRUCT_OFFSET (BookmarksPrivate, bookmarks_icon));
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "bookmarked_switch", FALSE, Bookmarks_private_offset + G_STRUCT_OFFSET (BookmarksPrivate, bookmarked_switch));
	gtk_widget_class_bind_template_callback_full (GTK_WIDGET_CLASS (klass), "bookmark_activated_cb", G_CALLBACK(_bookmarks_bookmark_activated_cb_gtk_list_box_row_activated));
}


static void bookmarks_path_element_interface_init (PathElementIface * iface) {
	bookmarks_path_element_parent_iface = g_type_interface_peek_parent (iface);
}


static void bookmarks_instance_init (Bookmarks * self) {
	gchar* _tmp0_;
	self->priv = BOOKMARKS_GET_PRIVATE (self);
	_tmp0_ = g_strdup ("/");
	self->priv->current_path = _tmp0_;
	self->priv->switch_active_handler = (gulong) 0;
	gtk_widget_init_template (GTK_WIDGET (self));
}


static void bookmarks_finalize (GObject * obj) {
	Bookmarks * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_BOOKMARKS, Bookmarks);
	_g_object_unref0 (self->priv->bookmarks_list_box);
	_g_object_unref0 (self->priv->bookmarks_popover);
	_g_object_unref0 (self->priv->bookmarks_icon);
	_g_object_unref0 (self->priv->bookmarked_switch);
	_g_free0 (self->priv->current_path);
	_g_free0 (self->priv->_schema_id);
	_g_object_unref0 (self->priv->settings);
	G_OBJECT_CLASS (bookmarks_parent_class)->finalize (obj);
}


GType bookmarks_get_type (void) {
	static volatile gsize bookmarks_type_id__volatile = 0;
	if (g_once_init_enter (&bookmarks_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (BookmarksClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) bookmarks_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Bookmarks), 0, (GInstanceInitFunc) bookmarks_instance_init, NULL };
		static const GInterfaceInfo path_element_info = { (GInterfaceInitFunc) bookmarks_path_element_interface_init, (GInterfaceFinalizeFunc) NULL, NULL};
		GType bookmarks_type_id;
		bookmarks_type_id = g_type_register_static (gtk_menu_button_get_type (), "Bookmarks", &g_define_type_info, 0);
		g_type_add_interface_static (bookmarks_type_id, TYPE_PATH_ELEMENT, &path_element_info);
		g_once_init_leave (&bookmarks_type_id__volatile, bookmarks_type_id);
	}
	return bookmarks_type_id__volatile;
}


static void _vala_bookmarks_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	Bookmarks * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, TYPE_BOOKMARKS, Bookmarks);
	switch (property_id) {
		case BOOKMARKS_SCHEMA_ID_PROPERTY:
		g_value_set_string (value, bookmarks_get_schema_id (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_bookmarks_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	Bookmarks * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, TYPE_BOOKMARKS, Bookmarks);
	switch (property_id) {
		case BOOKMARKS_SCHEMA_ID_PROPERTY:
		bookmarks_set_schema_id (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


Bookmark* bookmark_construct (GType object_type, const gchar* bookmark_name) {
	Bookmark * self = NULL;
	const gchar* _tmp0_;
	g_return_val_if_fail (bookmark_name != NULL, NULL);
	_tmp0_ = bookmark_name;
	self = (Bookmark*) g_object_new (object_type, "bookmark-name", _tmp0_, NULL);
	return self;
}


Bookmark* bookmark_new (const gchar* bookmark_name) {
	return bookmark_construct (TYPE_BOOKMARK, bookmark_name);
}


const gchar* bookmark_get_bookmark_name (Bookmark* self) {
	const gchar* result;
	const gchar* _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_bookmark_name;
	result = _tmp0_;
	return result;
}


static void bookmark_set_bookmark_name (Bookmark* self, const gchar* value) {
	g_return_if_fail (self != NULL);
	if (g_strcmp0 (value, bookmark_get_bookmark_name (self)) != 0) {
		const gchar* _tmp0_;
		gchar* _tmp1_;
		_tmp0_ = value;
		_tmp1_ = g_strdup (_tmp0_);
		_g_free0 (self->priv->_bookmark_name);
		self->priv->_bookmark_name = _tmp1_;
		g_object_notify_by_pspec ((GObject *) self, bookmark_properties[BOOKMARK_BOOKMARK_NAME_PROPERTY]);
	}
}


static GObject * bookmark_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	Bookmark * self;
	GtkLabel* _tmp0_;
	const gchar* _tmp1_;
	parent_class = G_OBJECT_CLASS (bookmark_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_BOOKMARK, Bookmark);
	_tmp0_ = self->priv->bookmark_label;
	_tmp1_ = self->priv->_bookmark_name;
	gtk_label_set_label (_tmp0_, _tmp1_);
	return obj;
}


static void bookmark_class_init (BookmarkClass * klass) {
	gint Bookmark_private_offset;
	bookmark_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (BookmarkPrivate));
	G_OBJECT_CLASS (klass)->get_property = _vala_bookmark_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_bookmark_set_property;
	G_OBJECT_CLASS (klass)->constructor = bookmark_constructor;
	G_OBJECT_CLASS (klass)->finalize = bookmark_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), BOOKMARK_BOOKMARK_NAME_PROPERTY, bookmark_properties[BOOKMARK_BOOKMARK_NAME_PROPERTY] = g_param_spec_string ("bookmark-name", "bookmark-name", "bookmark-name", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));
	Bookmark_private_offset = g_type_class_get_instance_private_offset (klass);
	gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass), "/ca/desrt/dconf-editor/ui/bookmark.ui");
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "bookmark_label", FALSE, Bookmark_private_offset + G_STRUCT_OFFSET (BookmarkPrivate, bookmark_label));
	gtk_widget_class_bind_template_child_full (GTK_WIDGET_CLASS (klass), "destroy_button", FALSE, G_STRUCT_OFFSET (Bookmark, destroy_button));
}


static void bookmark_instance_init (Bookmark * self) {
	self->priv = BOOKMARK_GET_PRIVATE (self);
	gtk_widget_init_template (GTK_WIDGET (self));
}


static void bookmark_finalize (GObject * obj) {
	Bookmark * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_BOOKMARK, Bookmark);
	_g_free0 (self->priv->_bookmark_name);
	_g_object_unref0 (self->priv->bookmark_label);
	_g_object_unref0 (self->destroy_button);
	G_OBJECT_CLASS (bookmark_parent_class)->finalize (obj);
}


GType bookmark_get_type (void) {
	static volatile gsize bookmark_type_id__volatile = 0;
	if (g_once_init_enter (&bookmark_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (BookmarkClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) bookmark_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Bookmark), 0, (GInstanceInitFunc) bookmark_instance_init, NULL };
		GType bookmark_type_id;
		bookmark_type_id = g_type_register_static (gtk_grid_get_type (), "Bookmark", &g_define_type_info, 0);
		g_once_init_leave (&bookmark_type_id__volatile, bookmark_type_id);
	}
	return bookmark_type_id__volatile;
}


static void _vala_bookmark_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	Bookmark * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, TYPE_BOOKMARK, Bookmark);
	switch (property_id) {
		case BOOKMARK_BOOKMARK_NAME_PROPERTY:
		g_value_set_string (value, bookmark_get_bookmark_name (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_bookmark_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	Bookmark * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, TYPE_BOOKMARK, Bookmark);
	switch (property_id) {
		case BOOKMARK_BOOKMARK_NAME_PROPERTY:
		bookmark_set_bookmark_name (self, g_value_get_string (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}


