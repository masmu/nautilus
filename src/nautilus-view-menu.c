#include <glib/gi18n.h>

#include "nautilus-view-menu.h"
#include "nautilus-actions.h"
#include "math.h"

struct _NautilusViewMenuPrivate
{
	GtkWidget *grid_button;
	GtkWidget *list_button;
	GtkWidget *zoom_level_scale;
	GtkWidget *sort_name;
	GtkWidget *sort_size;
	NautilusWindow *window;
};

enum
{
	ZOOM_LEVEL_CHANGED,
	LAST_SIGNAL
};

static guint signals [LAST_SIGNAL] = { 0 };

enum {
	PROP_WINDOW = 1,
	NUM_PROPERTIES
};

static GParamSpec *properties[NUM_PROPERTIES] = { NULL, };


G_DEFINE_TYPE_WITH_PRIVATE (NautilusViewMenu, nautilus_view_menu, GTK_TYPE_BOX)

static void
zoom_level_changed (GtkRange *range, NautilusViewMenu *self)
{
	gdouble zoom_level = gtk_range_get_value (range);
	g_printf("zoom level %f\n", zoom_level);
	g_signal_emit (self, signals[ZOOM_LEVEL_CHANGED], 0,
		       1, zoom_level,
		       G_TYPE_NONE);
}

static void
nautilus_toolbar_set_property (GObject *object,
			       guint property_id,
			       const GValue *value,
			       GParamSpec *pspec)
{
	NautilusViewMenu *self = NAUTILUS_VIEW_MENU (object);

	switch (property_id) {
	case PROP_WINDOW:
		self->priv->window = g_value_get_object (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
static void
nautilus_view_menu_finalize (GObject *object)
{
	NautilusViewMenu *self = NAUTILUS_VIEW_MENU (object);

	G_OBJECT_CLASS (nautilus_view_menu_parent_class)->finalize (object);
}

static void
nautilus_view_menu_constructed (GObject *obj)
{
	NautilusViewMenu *self = NAUTILUS_VIEW_MENU (obj);
	GtkActionGroup *action_group;
	GtkAction *action;

	G_OBJECT_CLASS (nautilus_view_menu_parent_class)->constructed (obj);

	action_group = nautilus_window_get_main_action_group (self->priv->window);

	action = gtk_action_group_get_action (action_group, NAUTILUS_ACTION_VIEW_GRID);
	gtk_activatable_set_related_action (GTK_ACTIVATABLE (self->priv->grid_button), action);
	gtk_button_set_label (GTK_BUTTON (self->priv->grid_button), NULL);

	action = gtk_action_group_get_action (action_group, NAUTILUS_ACTION_VIEW_LIST);
	gtk_activatable_set_related_action (GTK_ACTIVATABLE (self->priv->list_button), action);
	gtk_button_set_label (GTK_BUTTON (self->priv->list_button), NULL);

	action = gtk_action_group_get_action (action_group, "Sort by Name");
	//g_assert(action);
/*	g_printf ("ACTION TYPE %s\n", G_IS_OBJECT(action));
	gtk_activatable_set_related_action (GTK_ACTIVATABLE (self->priv->sort_name), action);

	action = gtk_action_group_get_action (action_group, "Sort by Size");
	gtk_activatable_set_related_action (GTK_ACTIVATABLE (self->priv->sort_size), action);
	*/
}

static void
nautilus_view_menu_class_init (NautilusViewMenuClass *klass)
{
	GObjectClass *object_class;
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = nautilus_view_menu_finalize;
	object_class->constructed = nautilus_view_menu_constructed;
	object_class->set_property = nautilus_toolbar_set_property;

	gtk_widget_class_set_template_from_resource (widget_class,
						 "/org/gnome/nautilus/nautilus-view-menu.ui");
	gtk_widget_class_bind_template_child_private(widget_class, NautilusViewMenu, grid_button);
	gtk_widget_class_bind_template_child_private(widget_class, NautilusViewMenu, list_button);
	gtk_widget_class_bind_template_child_private(widget_class, NautilusViewMenu, zoom_level_scale);
	gtk_widget_class_bind_template_child_private(widget_class, NautilusViewMenu, sort_name);
	gtk_widget_class_bind_template_child_private(widget_class, NautilusViewMenu, sort_size);

	signals [ZOOM_LEVEL_CHANGED] =
		g_signal_new ("zoom-level-changed",
			      G_TYPE_FROM_CLASS (object_class), G_SIGNAL_RUN_LAST,
			      0,
			      NULL, NULL,
			      g_cclosure_marshal_VOID__DOUBLE,
			      G_TYPE_NONE,
			      1, G_TYPE_DOUBLE);

	properties[PROP_WINDOW] =
		g_param_spec_object ("window",
				     "The NautilusWindow",
				     "The NautilusWindow this toolbar is part of",
				     NAUTILUS_TYPE_WINDOW,
				     G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY |
				     G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties (object_class, NUM_PROPERTIES, properties);
}

static void
nautilus_view_menu_init (NautilusViewMenu *self)
{
	GtkAdjustment * adj;
	self->priv = nautilus_view_menu_get_instance_private (self);
	gtk_widget_init_template (GTK_WIDGET (self));

	adj = gtk_range_get_adjustment (GTK_RANGE (self->priv->zoom_level_scale));
	g_signal_connect(self->priv->zoom_level_scale, "value-changed",
			 G_CALLBACK(zoom_level_changed),
			 self);
}

NautilusViewMenu *
nautilus_view_menu_new (NautilusWindow *window)
{
	g_assert (NAUTILUS_IS_WINDOW (window));
	NautilusViewMenu *self = g_object_new (NAUTILUS_TYPE_VIEW_MENU,
					       "window", window,
					       NULL);

	return self;
}
/* ex:set ts=8 noet: */
