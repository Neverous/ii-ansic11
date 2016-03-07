/* 2012
 * Maciej Szeptuch
 * II UWr
 * ----------
 *  GUI definitions.
 */
#ifndef _GUI_H
#define _GUI_H
#include<stdbool.h>
#include<gtk/gtk.h>

static const int MAX_VALUE = 1024,
			 	 MAX_ELEMENTS = 1024;

/*
 * Structure that keeps application state.
 */
typedef struct
{
	GtkWidget *mainWindow, // Pointer to GTK main window
			  *animationArea, // Pointer to animation drawing area
			  *algorithmSelection, // Pointer to algorithm selection box
			  *inputArea, // Pointer to input area
			  *controlButton; // Pointer to control button

	bool running; // Is the animation running?
	int array[1024], // Array to sort
		arraySize,
		width, // Width of animation
		height; // Height of animation

	GdkPixmap *animation; // Animation buffer
	void (*sort)(int *, const unsigned int); // Chosen sorting function
} AppState;

/*
 * Function that initializes the GUI.
 *	First argument is number of arguments passed through CLI, second is array
 *	of those.
 *	Sets up and draws all widgets etc.
 */
int initGUI(int argc, char *argv[]);

/*
 * Function that initializes main window of the GUI.
 *	First argument is pointer to AppState.
 *	Returns gtk window.
 */
GtkWidget *initMainWindow(AppState *state);

/*
 * Function that initializes animation area section.
 *	First argument is pointer to AppState.
 *	Returns widget representing animation area section.
 */
GtkWidget *initAnimationArea(AppState *state);

/*
 * Function that initializes input area section.
 *	First argument is pointer to AppState.
 *	Returns widget representing input area section.
 */
GtkWidget *initInputSection(AppState *state);

/*
 * Function that initializes algorithm selection and control buttons(ABOUT,
 * START/STOP).
 *	First argument is pointer to AppState.
 *	Returns widget representing control section.
 */
GtkWidget *initControlSection(AppState *state);

/* 
 * Function called when window manager tries to close the window.
 *	First argument is main window of application, second is pointer to AppState.
 *	Makes sure that we can close application. Stops animation etc.
 *	Returns TRUE if cannot close the application(we need to wait until animation
 *	stops) FALSE otherwise.
 */
gboolean deleteWindow(GtkWidget *widget, gpointer data);

/*
 * Function called on animation expose.
 *	First argument is main window of application, second is event information,
 *	third is pointer to AppState.
 *	Draws animation from pixmap to gtk drawable.
 */
gboolean exposeAnimation(GtkWidget *widget, GdkEventExpose *event,
						 gpointer data);

/*
 * Function called when animation area changes its size.
 *	First argument is pointer to animation area, second is event information,
 *	third is pointer to AppState.
 *	It makes sure that animation area fits the window.
 */
gboolean reconfigureAnimation(GtkWidget *widget, GdkEventConfigure *event,
							  gpointer data);

/*
 * Function that shows "About" dialog with basic informations about program.
 *	First argument is widget which triggered that callback, second is pointer
 *	to AppState.
 */
void showAbout(GtkWidget *widget, gpointer data);

/*
 * Function that randomizes input data 
 *	First argument is widget which triggered that callback, second is pointer
 *	to AppState.
 *	It shows dialog with input to set number of elements and then randomize them
 *	and saves in AppState.inputArea.
 */
void randomizeInputData(GtkWidget *widget, gpointer data);

/*
 * Function that parses input data.
 *	First argument is text to parse from input area, second is array for result.
 *	Returns false if input is wrong.
 */
bool parseInputData(char *text, int *result, int *size);

/* 
 * Function that start/stops animation.
 *	First argument is widget which triggered that callback, second is pointer
 *	to AppState.
 *	If animation is stopped it parses input data from AppState.inputArea
 *	and checks if numbers are correct etc. It also checks if algorithm
 *	is selected. Then it starts animation.
 *	If animation is started it stops it.
 */
void toggleAnimation(GtkWidget *widget, gpointer data);

/*
 * Function that returns active id(second column in model) of given GtkComboBox.
 *	First argument is GtkComboBox to get active element from.
 *	Returns id of active element. If none active returns -1.
 */
int getComboBoxActiveID(GtkComboBox *combo);

/*
 * Function that returns text of given GtkTextView.
 *	First argument is GtkTextView to get text from.
 *	Returns pointer to text buffer.
 */
char *getTextBuffer(GtkTextView *view);

/*
 * Function that prepare for and start sorting. Runs as separate thread.
 *	First argument is pointer to AppState.
 */
void *startSorting(void *data);

/*
 * Function that returns application state.
 */
AppState *getAppState(void);

/* DRAWING FUNCTIONS */
/*
 * Function that creates surface for animation.
 *	First argument is application state.
 *	It draws actual frame of animation or empty black if is stopped.
 */
cairo_surface_t *createAnimationSurface(AppState *state);

/*
 * Function that draws specified column on animation area.
 *	First argument is position in array, second is color id, last is application
 *	state.
 */
void drawColumn(int number, int color, AppState *state);
#endif
