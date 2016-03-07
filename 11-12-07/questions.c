/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<gtk/gtk.h>

#define QUESTION_LENGTH 1024
#define ANSWER_LENGTH 1024
#define QUESTIONS_ASK 10
#define QUESTIONS 30

typedef struct quest
{
	char question[QUESTION_LENGTH],
		 answer[4][ANSWER_LENGTH];
	unsigned int correct;
} Question;

typedef struct appState
{
	unsigned int question, // Actual question ID
				 good, // Good answers
				 count; // Good answers count
	gboolean blocked; // Signals blocked?
	GtkWidget *window, // Main window
			  *answerBox[4], // Answer box
			  *answerLabel[4], // Answer text
			  *questionLabel; // Question text
} AppState;

Question question[QUESTIONS]; // Avaliable questions
unsigned int questions; // Questions count

inline static void declareQuestion(char *quest, char *a, char *b, char *c, char *d, const unsigned int correct); // Declare question
inline static void generateQuestions(void); // Generate questions
inline static const unsigned int chooseQuestion(void); // Choose next question

/* WINDOW CALLBACKS */
inline static void destroyWindow(GtkWidget *widget, gpointer data);
inline static const gboolean showSummary(GtkWidget *widget, GdkEvent *event, gpointer data); // Show summary and ask if continue

/* APP CALLBACKS */
inline static void answerChoice(GtkWidget *widget, gpointer data);
inline static gboolean updateQuestion(gpointer data); // Update window to the next question

int main(int argc, char *argv[])
{
	srand(time(NULL));
	generateQuestions();

	/* Generate Questionnaire Window */
	char label[1024];
	GtkWidget *windowBox, // Horizontal box
			  *answerButton[4], // Answer button
			  *tempBox; // For event box background coloring
	AppState state; // State of application

	state.question = chooseQuestion(); // Choose first question
	state.good = state.count = 0;

	gtk_init(&argc, &argv);
	/* MAIN WINDOW */
	state.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	sprintf(label, "%d Questions? 1/%d", QUESTIONS_ASK, QUESTIONS_ASK);
	gtk_window_set_title(GTK_WINDOW(state.window), label);
	gtk_window_set_default_size(GTK_WINDOW(state.window), 400, 300);
	gtk_window_set_position(GTK_WINDOW(state.window), GTK_WIN_POS_CENTER);
	g_signal_connect(state.window, "destroy", G_CALLBACK(destroyWindow), NULL); // Destroy callback
	g_signal_connect(state.window, "delete-event", G_CALLBACK(showSummary), &state); // Closing callback

	/* MAIN BOX */
	windowBox = gtk_vbox_new(TRUE, 5);

	/* FIRST QUESTION */
	state.questionLabel = gtk_label_new(question[state.question].question);
	gtk_box_pack_start(GTK_BOX(windowBox), state.questionLabel, TRUE, FALSE, 0);

	/* ANSWERS */
	for(int a = 0; a < 4; ++ a)
	{
		state.answerBox[a] = gtk_hbox_new(FALSE, 5);

		/* BUTTON */
		sprintf(label, "%c", 'A' + a);
		answerButton[a] = gtk_button_new_with_label(label);
		gtk_widget_set_usize(answerButton[a], 60, 60);
		g_signal_connect(answerButton[a], "clicked", G_CALLBACK(answerChoice), &state);

		/* ANSWERS */
		state.answerLabel[a] = gtk_label_new(question[state.question].answer[a]);

		/* BOXING */
		gtk_box_pack_start(GTK_BOX(state.answerBox[a]), answerButton[a], FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(state.answerBox[a]), state.answerLabel[a], FALSE, FALSE, 0);

		/* ALLOW CHANGES BACKGROUND COLOR THROUGH GTK EVENT BOX */
		tempBox = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(tempBox), state.answerBox[a]);
		state.answerBox[a] = tempBox;

		gtk_box_pack_start(GTK_BOX(windowBox), state.answerBox[a], FALSE, FALSE, 0);
	}

	/* RUN GTK APP */
	gtk_container_add(GTK_CONTAINER(state.window), windowBox);
	gtk_widget_show_all(state.window);
	gtk_main();
	return 0;
}

inline static void answerChoice(GtkWidget *widget, gpointer data)
{
	unsigned int answer = gtk_button_get_label(GTK_BUTTON(widget))[0] - 'A'; // user answer
	AppState *state = (AppState *)data;
	GdkColor wrong, // Color of bad answer
			 good; // Color of good answer
	Question act = question[state->question]; // act question
	if(state->blocked == TRUE) // Window blocked - showing results and waiting for next draw
		return;

	++ state->count;
	state->blocked = TRUE; // Block window

	gdk_color_parse("darkred", &wrong);
	gdk_color_parse("darkgreen", &good);

	if(act.correct != answer) // WA
		gtk_widget_modify_bg(state->answerBox[answer], GTK_STATE_NORMAL, &wrong);

	else
		++ state->good;

	gtk_widget_modify_bg(state->answerBox[act.correct], GTK_STATE_NORMAL, &good); // OK
	g_timeout_add(2000, updateQuestion, state); // Wait 2 seconds before updating to next question/summary
	return;
}

inline static gboolean updateQuestion(gpointer data)
{
	AppState *state = (AppState *)data;
	Question act;
	char label[1024];

	if(state->count == QUESTIONS_ASK)
	{
		if(showSummary(NULL, NULL, state) == FALSE) // all questions and user choose to end game
			destroyWindow(NULL, NULL);

		else // clear state
			state->count = state->good = 0;
	}

	state->blocked = FALSE;

	/* GET NEW QUESTION */
	act = question[state->question = chooseQuestion()];

	//Update labels
	gtk_label_set_text(GTK_LABEL(state->questionLabel), act.question);
	for(int a = 0; a < 4; ++ a)
	{
		gtk_widget_modify_bg(state->answerBox[a], GTK_STATE_NORMAL, NULL); // clear background
		gtk_label_set_text(GTK_LABEL(state->answerLabel[a]), act.answer[a]);
	}

	sprintf(label, "%d Questions? %d/%d", QUESTIONS_ASK, state->count + 1, QUESTIONS_ASK);
	gtk_window_set_title(GTK_WINDOW(state->window), label); // Update window title
	return FALSE;
}

inline static const gboolean showSummary(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	GtkWidget *summary,
			  *info;
	AppState *state = (AppState *) data;
	char label[1024];
	unsigned int result;

	summary = gtk_dialog_new_with_buttons("Summary", GTK_WINDOW(state->window), GTK_DIALOG_MODAL,
		"Yes", GTK_RESPONSE_ACCEPT,
		"No", GTK_RESPONSE_REJECT,
	NULL); // Dialog with message

	if(state->count == QUESTIONS_ASK)
		sprintf(label, "You answered %d questions correct. Do you want another test?", state->good);

	else
		sprintf(label, "%d questions left. Do you want to continue?", QUESTIONS_ASK - state->count);

	info = gtk_label_new(label);
	gtk_widget_show(info);
	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(summary))), info, FALSE, FALSE, 0);

	result = gtk_dialog_run(GTK_DIALOG(summary));
	gtk_widget_destroy(summary);
	return result == GTK_RESPONSE_ACCEPT?TRUE:FALSE;
}

inline static void destroyWindow(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	return;
}

inline static const unsigned int chooseQuestion(void)
{
	return rand() % questions;
}

inline static void generateQuestions(void)
{
	declareQuestion(
		"What happened to the flowers?",
		"They faded in autumn.",
		"They were eaten by goats.",
		"They were picked by girls.",
		"They were picked by boys.",
		1
	);
	declareQuestion(
		"What does Macky have?",
		"A pirate ship.",
		"A knife.",
		"Teeth.",
		"Three pennies.",
		2
	);
	declareQuestion(
		"What does Macky have?",
		"A pirate ship.",
		"A knife.",
		"Teeth.",
		"Three pennies.",
		2
	);
	declareQuestion(
		"What does Catharina protect?",
		"The motherland.",
		"The walls of the city.",
		"The love.",
		"The treasure.",
		3
	);
	declareQuestion(
		"2 + 2 = ?",
		"0",
		"4",
		"1",
		"2",
		1
	);
	declareQuestion(
		"Who played Mrs Columbo?",
		"Peter Falk",
		"Kate Mulgrew",
		"Joan Hickson",
		"She was never seen",
		1
	);
	declareQuestion(
		"Who was the first person to play James Bond 007?",
		"Sean Connery",
		"David Niven",
		"Woody Allen",
		"Bob Holness",
		3
	);
	declareQuestion(
		"Brontophobia is the fear of?",
		"Coughing",
		"Slime",
		"Thunder",
		"Dinosaurs",
		2
	);
	declareQuestion(
		"Hester Grenville was related to a British Prime Minister but was she his",
		"Sister",
		"Mother",
		"Wife",
		"All three",
		3
	);
	declareQuestion(
		"Worlds to Barta was released under the pen name John Beynon Harris but under what name is he more famous?",
		"John Wyndam",
		"Steve King",
		"Stan Lee",
		"J R R Tolkien",
		0
	);
	declareQuestion(
		"What last occured in 1882 that will occur again on the 8th June 2004?",
		"Mars passed between the Sun and Earth",
		"Mercury passed between the Sun and Earth",
		"Venus passed between the Sun and Earth",
		"The Liberals won an election",
		2
	);
	declareQuestion(
		"Which of the following was not a Private Eye?",
		"Frank Marker",
		"Harry Orwell",
		"Jim Rockford",
		"Des Kinvig",
		3
	);
	declareQuestion(
		"In which series by Carla Lane did she first write about the Boswells?",
		"Bread",
		"The Liver Birds",
		"Butterflies",
		"Luv",
		1
	);
	declareQuestion(
		"What did mother make in the 1970's according to Richard Waring?",
		"Cakes",
		"Oxo",
		"Five",
		"Trouble",
		2
	);
	declareQuestion(
		"Which of the following was not the Invisable Man?",
		"Dr Richards",
		"Dr Brady",
		"Dr Weston",
		"Dr Griffin",
		0
	);
	declareQuestion(
		"What does the Spanish word 'mar' mean in English?",
		"Sea",
		"Bee",
		"A",
		"Dee",
		0
	);
	declareQuestion(
		"Lizards belong to which animal group?",
		"Amphibians",
		"Reptiles",
		"Invertebrates",
		"Mammals",
		1
	);
	declareQuestion(
		"H2O is the chemical formula of:",
		"hydrogen peroxide",
		"ozone",
		"ammonia",
		"water",
		3
	);
	declareQuestion(
		"The nucleus of an atom consists of:",
		"electrons",
		"neutrons",
		"protons and neutrons",
		"protons, neutrons and electrons",
		2
	);
	declareQuestion(
		"The third planet from the sun is:",
		"Mercury",
		"Mars",
		"Earth",
		"Venus",
		2
	);
	declareQuestion(
		"Entomology is the scientific study of:",
		"internal organs",
		"meanings of words",
		"trees",
		"insects",
		3
	);
	declareQuestion(
		"The green pigment found in plants that performs photosynthesis is:",
		"melanin",
		"chlorophyll",
		"chromatophore",
		"chloroplast",
		1
	);
	declareQuestion(
		"An android is a robot that:",
		"is made to resemble a human in some way",
		"can make decisions or think for itself to some extent",
		"has been built to perform multiple tasks",
		"was built by a machine or other robots",
		0
	);
	declareQuestion(
		"A proton has what electrical charge?",
		"no charge",
		"positive charge",
		"negative charge",
		"either a positive or negative charge",
		1
	);
	declareQuestion(
		"How many legs do insects have?",
		"4",
		"6",
		"some have 6m some have 8",
		"8",
		1
	);
	declareQuestion(
		"The ozone layer protects us from too much:",
		"carbon dioxide",
		"gamma radiation",
		"temperature fluctuation",
		"ultraviolet radiation",
		3
	);
}

inline static void declareQuestion(char *quest, char *a, char *b, char *c, char *d, const unsigned int correct)
{
	if(questions == QUESTIONS)
		exit(1337);

	strcpy(question[questions].question, quest);
	strcpy(question[questions].answer[0], a);
	strcpy(question[questions].answer[1], b);
	strcpy(question[questions].answer[2], c);
	strcpy(question[questions].answer[3], d);
	question[questions ++].correct = correct;
}
