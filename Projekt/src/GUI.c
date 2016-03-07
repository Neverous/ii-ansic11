/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#define _POSIX_C_SOURCE 199309L //Needed for nanosleep
#include<stdlib.h>
#include<ctype.h>
#include<gtk/gtk.h>
#include<pthread.h>
#include<signal.h>
#include<time.h>
#include "GUI.h"
#include "algorithms/algorithms.h"

static AppState appstate = {NULL, NULL, NULL, NULL, NULL, FALSE, {0}, 0, 0, 0,
							NULL, NULL};

int initGUI(int argc, char *argv[])
{
	GtkWidget *mainBox = NULL, // Main layout,
			  *bottom = NULL; // Bottom section(input|control)
	srand(time(NULL)); // Initialize random

	// Init threading
	if(!g_thread_supported())
		g_thread_init(NULL);

	gdk_threads_init();
	gdk_threads_enter();

	// Init gtk
	gtk_init(&argc, &argv);
	initMainWindow(&appstate);
	mainBox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainBox), initAnimationArea(&appstate), TRUE,
					   TRUE, 0);

	bottom = gtk_hbox_new(FALSE, 0);
	gtk_widget_set_size_request(bottom, -1, 150);
	gtk_box_pack_start(GTK_BOX(bottom), initInputSection(&appstate), TRUE, TRUE,
					   0);
	gtk_box_pack_start(GTK_BOX(bottom), initControlSection(&appstate), FALSE,
					   FALSE, 0);
	gtk_box_pack_start(GTK_BOX(mainBox), bottom, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(appstate.mainWindow), mainBox);
	gtk_widget_show_all(appstate.mainWindow);
	gtk_main();
	gdk_threads_leave();
	return 0;
}

GtkWidget *initMainWindow(AppState *state)
{
	state->mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(state->mainWindow),
						 "Sorting Algorithms Visualization");
	gtk_window_set_default_size(GTK_WINDOW(state->mainWindow), 800, 400);
	gtk_window_set_position(GTK_WINDOW(state->mainWindow), GTK_WIN_POS_CENTER);
	g_signal_connect(state->mainWindow, "destroy", G_CALLBACK(gtk_main_quit),
					 &state);
	g_signal_connect(state->mainWindow, "delete-event",
					 G_CALLBACK(deleteWindow), &state);
	return state->mainWindow;
}

GtkWidget *initAnimationArea(AppState *state)
{
	state->animationArea = gtk_drawing_area_new();
	gtk_widget_set_double_buffered(state->animationArea, FALSE);
	g_signal_connect(state->animationArea, "configure-event",
					 G_CALLBACK(reconfigureAnimation), state);
	g_signal_connect(state->animationArea, "expose-event",
					 G_CALLBACK(exposeAnimation), state);
	return state->animationArea;
}

GtkWidget *initInputSection(AppState *state)
{
	GtkWidget *hbox = gtk_hbox_new(FALSE, 0), // Horizontal layout for label
			  								  // and randomize button
			  *vbox = gtk_vbox_new(FALSE, 0), // Vertical layout
			  *widget = NULL;
	char label[1024] = {};
	g_snprintf(label, 1024, "Input data(Max %d elements, 0-%d):", MAX_ELEMENTS,
			   MAX_VALUE);

	gtk_box_pack_start(GTK_BOX(hbox),
		gtk_label_new(label), TRUE, TRUE, 0);
	widget = gtk_button_new_with_label("Randomize");
	gtk_button_set_image(GTK_BUTTON(widget),
		gtk_image_new_from_stock(GTK_STOCK_EXECUTE, GTK_ICON_SIZE_BUTTON));
	g_signal_connect(widget, "clicked", G_CALLBACK(randomizeInputData), state);
	gtk_box_pack_start(GTK_BOX(hbox), widget, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	
	widget = gtk_scrolled_window_new(NULL, NULL);
	state->inputArea = gtk_text_view_new();
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(state->inputArea), GTK_WRAP_WORD);
	gtk_container_add(GTK_CONTAINER(widget), state->inputArea);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widget),
								   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(vbox), widget, TRUE, TRUE, 0);
	return vbox;
}

GtkWidget *initControlSection(AppState *state)
{
	GtkWidget *vbox = gtk_vbox_new(FALSE, 0), // Vertical layout
			  *hbox = gtk_hbox_new(FALSE, 0), // Horizontal layout for buttons
			  *widget = NULL;
	GtkTreeIter last;
	GtkCellRenderer *render = gtk_cell_renderer_text_new();
	GtkListStore *algorithms = gtk_list_store_new(2, G_TYPE_STRING,
												  G_TYPE_UINT);
	Algorithm *algo = getAvailableAlgorithms();
	for(unsigned int i = 0; algo[i].name != NULL; ++ i)
		if(algo[i].function != NULL)
		{
			gtk_list_store_append(algorithms, &last);
			gtk_list_store_set(algorithms, &last,
				0, algo[i].name,
				1, i,
				-1);
		}

	state->algorithmSelection = gtk_combo_box_new_with_model(
		GTK_TREE_MODEL(algorithms));
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(state->algorithmSelection),
		render, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(state->algorithmSelection),
		render, "text", 0, NULL);

	gtk_box_pack_start(GTK_BOX(vbox), gtk_label_new("Algorithm:"), FALSE, FALSE,
					   0);
	gtk_box_pack_start(GTK_BOX(vbox), state->algorithmSelection, FALSE, FALSE,
					   0);

	widget = gtk_button_new_with_label("ABOUT");
	gtk_button_set_image(GTK_BUTTON(widget),
		gtk_image_new_from_stock(GTK_STOCK_ABOUT, GTK_ICON_SIZE_BUTTON));
	gtk_widget_set_size_request(widget, 100, 50);
	g_signal_connect(widget, "clicked", G_CALLBACK(showAbout), state);
	gtk_box_pack_start(GTK_BOX(hbox), widget, TRUE, FALSE, 0);

	widget = state->controlButton = gtk_button_new_with_label("START");
	gtk_button_set_image(GTK_BUTTON(widget),
		gtk_image_new_from_stock(GTK_STOCK_YES, GTK_ICON_SIZE_BUTTON));
	gtk_widget_set_size_request(widget, 150, 50);
	g_signal_connect(widget, "clicked", G_CALLBACK(toggleAnimation), state);
	gtk_box_pack_start(GTK_BOX(hbox), widget, TRUE, FALSE, 0);

	widget = gtk_alignment_new(0, 1, 0, 0);
	gtk_container_add(GTK_CONTAINER(widget), hbox);
	gtk_box_pack_start(GTK_BOX(vbox), widget, TRUE, TRUE, 0);
	return vbox;
}

gboolean deleteWindow(GtkWidget *widget, gpointer data)
{
	AppState *state = (AppState *)data;
	if(state->running)
		toggleAnimation(widget, data);

	return state->running?TRUE:FALSE;
}

gboolean exposeAnimation(GtkWidget *widget, GdkEventExpose *event,
						 gpointer data)
{
	AppState *state = (AppState *)data;
	gdk_draw_drawable(widget->window,
		widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
		state->animation,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);

	return TRUE;
}

gboolean reconfigureAnimation(GtkWidget *widget, GdkEventConfigure *event,
							  gpointer data)
{
	AppState *state = (AppState *)data;
	cairo_surface_t *surface = NULL; // New resized surface
	if(state->width == event->width && state->height == event->height)
		return TRUE;

	state->width = event->width;
	state->height = event->height;
	surface = createAnimationSurface(state);
	if(state->animation)
		g_object_unref(state->animation);

	state->animation = gdk_pixmap_new(state->animationArea->window,
									  state->width, state->height, -1);
	cairo_t *context = gdk_cairo_create(state->animation);
	cairo_set_source_surface(context, surface, 0, 0);
	cairo_paint(context);
	cairo_destroy(context);
	cairo_surface_destroy(surface);
	return TRUE;
}

void showAbout(GtkWidget *widget, gpointer data)
{
	AppState *state = (AppState *)data;
	gtk_show_about_dialog(
		GTK_WINDOW(state->mainWindow),
		"logo-icon-name", GTK_STOCK_DIALOG_QUESTION,
		"program-name", "Sorting Algorithm Visualization",
		"comments", "Simple visualization of various sorting algorithms.",
		"version", "0.1",
		"copyright", "Maciej Szeptuch 2012",
		NULL);

	return;
}

void randomizeInputData(GtkWidget *widget, gpointer data)
{
	AppState *state = (AppState *)data;
	GtkWidget *dialog = NULL, // Dialog for number of elements
			  *input = NULL,
			  *content = NULL,
			  *vbox = NULL;
	int res = 0, // Dialog result code
		numbers = 0, // Number of elements
		reslen = 0; // Length of result string
	char result[65536] = {};
	if(state->running)
		return;

	dialog = gtk_dialog_new_with_buttons(
		"Randomize input",
		GTK_WINDOW(state->mainWindow),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_STOCK_CANCEL,
		GTK_RESPONSE_NONE,
		GTK_STOCK_OK,
		GTK_RESPONSE_ACCEPT,
		NULL);

	content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),
		gtk_label_new("Set number of elements:"), FALSE, FALSE, 0);
	input = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input), 4);
	gtk_box_pack_start(GTK_BOX(vbox), input, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(content), vbox);
	gtk_widget_show_all(vbox);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	numbers = atoi(gtk_entry_get_text(GTK_ENTRY(input)));
	if(res == GTK_RESPONSE_NONE)
	{
		gtk_widget_destroy(dialog);
		return;
	}

	gtk_widget_set_sensitive(dialog, FALSE);
	if(numbers > MAX_ELEMENTS)
		numbers = MAX_ELEMENTS;

	for(int n = 0; n < numbers; ++ n)
		reslen += snprintf(result + reslen, 65536 - reslen, "%s%d", n?", ":"",
						   rand() % MAX_VALUE);

	gtk_text_buffer_set_text(gtk_text_view_get_buffer(
		GTK_TEXT_VIEW(state->inputArea)), result, -1);
	gtk_widget_destroy(dialog);
	return;
}

bool parseInputData(char *text, int *array, int *size)
{
	if(text == NULL || !text[0] || array == NULL) // text is empty
		return FALSE;

	bool lastDelim = true; // last char was whitespace or comma
	int a = 0; // position of last number in array
	array[0] = 0;
	for(int t = 0; text[t]; ++ t)
	{
		if(isspace(text[t]) || text[t] == ',')
		{
			if(!lastDelim)
			{
				if(array[a] > MAX_VALUE) // Invalid input
					return FALSE;

				array[++ a] = 0;
			}

			lastDelim = true;
			continue;
		}

		lastDelim = false;
		if(!isdigit(text[t])) // Invalid input
			return FALSE;

		array[a] = array[a] * 10 + text[t] - '0';
	}
	
	if(!lastDelim)
	{
		if(array[a] > MAX_VALUE) // Invalid input
			return FALSE;

		++ a;
	}

	*size = a;
	return TRUE;
}

void toggleAnimation(GtkWidget *widget, gpointer data)
{
	AppState *state = (AppState *)data;
	int algorithm = -1; // choosen algorithm id
	Algorithm *algo = NULL; // Array of available algorithms
	char *input = NULL; // Input data
	GtkWidget *message = NULL;
	static pthread_t thread;
	if(state->running) // working, request stop
	{
		state->running = FALSE;
		gtk_button_set_image(GTK_BUTTON(widget),
			gtk_image_new_from_stock(GTK_STOCK_YES, GTK_ICON_SIZE_BUTTON));
		gtk_button_set_label(GTK_BUTTON(widget), "START");
		// unblock all
		gtk_widget_set_sensitive(state->algorithmSelection, TRUE);
		gtk_widget_set_sensitive(gtk_widget_get_parent(gtk_widget_get_parent(
			state->inputArea)), TRUE);
		return;
	}

	algo = getAvailableAlgorithms();
	input = getTextBuffer(GTK_TEXT_VIEW(state->inputArea));
	algorithm = getComboBoxActiveID(GTK_COMBO_BOX(state->algorithmSelection));
	if(algorithm == -1 || !parseInputData(input, state->array,
		&state->arraySize) || algo[algorithm].function == NULL) // Wrong input
	{
		message = gtk_message_dialog_new(
			GTK_WINDOW(state->mainWindow),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE,
			"Error: Wrong input! Check algorithm selection and input data.");
		gtk_dialog_run(GTK_DIALOG(message));
		gtk_widget_destroy(message);
		free(input);
		return;
	}

	// DATA IS OK
	free(input);
	gtk_button_set_image(GTK_BUTTON(widget),
		gtk_image_new_from_stock(GTK_STOCK_NO, GTK_ICON_SIZE_BUTTON));
	gtk_button_set_label(GTK_BUTTON(widget), "STOP");
	// block algorithm selection
	gtk_widget_set_sensitive(state->algorithmSelection, FALSE);
	// block input area
	gtk_widget_set_sensitive(gtk_widget_get_parent(gtk_widget_get_parent(
		state->inputArea)), FALSE);

	state->sort = algo[algorithm].function;
	/* START SORTING */
	state->running = TRUE;
	pthread_create(&thread, NULL, startSorting, state);
	return;
}

int getComboBoxActiveID(GtkComboBox *combo)
{
	GtkTreeIter iter;
	GtkTreeModel *model = NULL;
	int result = -1;
	if(gtk_combo_box_get_active_iter(combo, &iter))
	{
		model = gtk_combo_box_get_model(combo);
		gtk_tree_model_get(model, &iter, 1, &result, -1);
	}

	return result;
}

char *getTextBuffer(GtkTextView *view)
{
	GtkTextIter start,
				end;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(view);

	gtk_text_buffer_get_bounds(buffer, &start, &end);
	return gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
}

void *startSorting(void *data)
{
	AppState *state = (AppState *)data;
	/* PREPARE ANIMATION AREA */
	cairo_surface_t *surface = createAnimationSurface(state);
	cairo_t *context = NULL;

	gdk_threads_enter();
	context = gdk_cairo_create(state->animation);
	cairo_set_source_surface(context, surface, 0, 0);
	cairo_paint(context);
	gtk_widget_queue_draw_area(state->animationArea, 0, 0, state->width,
							   state->height);
	cairo_destroy(context);
	gdk_threads_leave();

	cairo_surface_destroy(surface);
	/* START SORTING */
	state->sort(state->array, state->arraySize);
	if(state->running)
		toggleAnimation(state->controlButton, state);

	return NULL;
}

cairo_surface_t *createAnimationSurface(AppState *state)
{
	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
		state->width, state->height);
	cairo_t *context = cairo_create(surface);
	cairo_set_source_rgb(context, 0, 0, 0);
	cairo_rectangle(context, 0, 0, state->width, state->height);
	cairo_fill(context);
	float columnWidth = 0.0,
		  columnHeight = 0.0;
	
	if(state->running)
	{
		columnWidth = (float)state->width / state->arraySize;
		cairo_set_source_rgb(context, 1, 1, 1);
		for(int a = 0; a < state->arraySize; ++ a)
		{
			columnHeight = (float)state->array[a] * state->height / MAX_VALUE;
			cairo_rectangle(context, columnWidth * a, state->height -
				columnHeight, columnWidth, columnHeight);
		}

		cairo_fill(context);
	}

	cairo_destroy(context);
	return surface;
}

AppState *getAppState(void)
{
	return &appstate;
}

void drawColumn(int number, int color, AppState *state)
{
	if(!state->running)
		return;

	gdk_threads_enter();
	cairo_t *context = gdk_cairo_create(state->animation);
	float columnWidth = (float)state->width / state->arraySize,
		  columnHeight = (float)state->array[number] * state->height 
			  			 / MAX_VALUE;
	
	cairo_set_source_rgb(context, 0, 0, 0);
	cairo_rectangle(context, columnWidth * number, 0, columnWidth, state->height
					- columnHeight);
	cairo_fill(context);

	int red = color >> 16,
		green = (color >> 8) & 0xFF,
		blue = color & 0xFF;
	cairo_set_source_rgb(context, (float)red / 256, (float)green / 256,
						 (float)blue / 256);
	cairo_rectangle(context, columnWidth * number, state->height -
			columnHeight, columnWidth, columnHeight);
	cairo_fill(context);
	cairo_destroy(context);
	gtk_widget_queue_draw_area(state->animationArea, columnWidth * number, 0,
							   columnWidth * (number + 1), state->height);
	struct timespec sec = {0, 50000}; // 0.00005s
	nanosleep(&sec, NULL);
	gdk_threads_leave();
	return;
}
