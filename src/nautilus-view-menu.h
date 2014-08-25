/* nautilus-view-menu.h
 *
 * Copyright (C) 2014 Carlos Soriano <carlos.soriano89@gmail.com>
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NAUTILUS_VIEW_MENU_H
#define NAUTILUS_VIEW_MENU_H

#include <glib-object.h>
#include <gtk/gtk.h>
#include "nautilus-window.h"

G_BEGIN_DECLS

#define NAUTILUS_TYPE_VIEW_MENU            (nautilus_view_menu_get_type())
#define NAUTILUS_VIEW_MENU(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), NAUTILUS_TYPE_VIEW_MENU, NautilusViewMenu))
#define NAUTILUS_VIEW_MENU_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), NAUTILUS_TYPE_VIEW_MENU, NautilusViewMenu const))
#define NAUTILUS_VIEW_MENU_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  NAUTILUS_TYPE_VIEW_MENU, NautilusViewMenuClass))
#define NAUTILUS_IS_VIEW_MENU(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NAUTILUS_TYPE_VIEW_MENU))
#define NAUTILUS_IS_VIEW_MENU_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  NAUTILUS_TYPE_VIEW_MENU))
#define NAUTILUS_VIEW_MENU_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  NAUTILUS_TYPE_VIEW_MENU, NautilusViewMenuClass))

typedef struct _NautilusViewMenu        NautilusViewMenu;
typedef struct _NautilusViewMenuClass   NautilusViewMenuClass;
typedef struct _NautilusViewMenuPrivate NautilusViewMenuPrivate;

struct _NautilusViewMenu
{
    GtkBox parent;

    /*< private >*/
    NautilusViewMenuPrivate *priv;
};

struct _NautilusViewMenuClass
{
    GtkBoxClass parent_class;
    void (*zoom_level_changed) (NautilusViewMenu *view_menu);
};

GType nautilus_view_menu_get_type (void) G_GNUC_CONST;

NautilusViewMenu * nautilus_view_menu_new (NautilusWindow *window);

G_END_DECLS

#endif /* NAUTILUS_VIEW_MENU_H */
