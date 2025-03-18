#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_FILENAME_LENGTH 60
#define MIN_PASSWORD_LENGTH 8

// Global variables
char current_user[MAX_USERNAME_LENGTH] = "";
GtkWidget *username_entry;
GtkWidget *password_entry;
GtkWidget *login_window;
void open_diary(GtkWidget *widget, gpointer data);
void create_login_window(void);
void apply_css(void);
// Function prototypes

void open_diary(GtkWidget *widget, gpointer data);
void create_login_window(void);
void handle_back(GtkWidget *widget, gpointer data);

// Modified handle_back function
void handle_back(GtkWidget *widget, gpointer diary_window) {
    // Disconnect the "destroy" signal handler from diary window
    g_signal_handlers_disconnect_by_func(diary_window, G_CALLBACK(gtk_main_quit), NULL);
    
    // Destroy current diary window
    gtk_widget_destroy(GTK_WIDGET(diary_window));
    
    // Create and show new login window
    create_login_window();
}


// css style 
const char *css_data = "\
    /* Login window with original style */\
    .login-window {\
        background: linear-gradient(135deg, #fff5e6 0%, #ffe6e6 100%);\
        background-size: 200% 200%;\
        animation: gradient 15s ease infinite;\
    }\
    \
    @keyframes gradient {\
        0% { background-position: 0% 50%; }\
        50% { background-position: 100% 50%; }\
        100% { background-position: 0% 50%; }\
    }\
    \
    /* Enhanced diary window with ruled paper background */\
    .diary-window {\
        background: #ffffff;\
        background-image: linear-gradient(#d1e3f9 1px, transparent 1px);\
        background-size: 100% 25px;\
        box-shadow: inset 0 0 100px rgba(0, 0, 0, 0.05);\
    }\
    \
    /* Updated dialog styling with light blue theme */\
    dialog, messagedialog {\
        background: linear-gradient(135deg, #f0f8ff 0%, #e6f3ff 100%);\
        border: 2px solid #b3d9ff;\
        border-radius: 12px;\
        box-shadow: 0 8px 25px rgba(0, 0, 0, 0.1),\
                   0 4px 12px rgba(179, 217, 255, 0.3);\
        padding: 20px;\
    }\
    \
    /* Updated dialog text */\
    dialog label, messagedialog label {\
        color: #2c5282;\
        font-size: 15px;\
        font-weight: 500;\
        line-height: 1.6;\
        margin: 12px;\
        padding: 8px;\
        text-shadow: 1px 1px 1px rgba(255, 255, 255, 0.9);\
    }\
    \
    /* Updated dialog buttons */\
    dialog button, messagedialog button {\
        background: linear-gradient(to bottom, #ffffff, #f0f4f8);\
        color: #2c5282;\
        font-weight: bold;\
        padding: 8px 20px;\
        font-size: 14px;\
        border-radius: 8px;\
        margin: 6px;\
        border: 1px solid #b3d9ff;\
        box-shadow: 0 4px 6px rgba(0, 0, 0, 0.05),\
                   0 2px 4px rgba(179, 217, 255, 0.2);\
        transition: all 0.2s ease;\
    }\
    \
    dialog button:hover, messagedialog button:hover {\
        background: linear-gradient(to bottom, #f8fafc, #e6f3ff);\
        transform: translateY(-1px);\
        box-shadow: 0 6px 12px rgba(0, 0, 0, 0.08),\
                   0 3px 6px rgba(179, 217, 255, 0.3);\
    }\
    \
    textview {\
        background-color: rgba(255, 255, 255, 0.95);\
        color: #333333;\
        border: 1px solid #e6d5c5;\
        border-radius: 10px;\
        padding: 25px;\
        font-size: 18px;\
    }\
    \
    textview text {\
        background-color: transparent;\
        color: #333333;\
        font-size: 18px;\
        line-height: 1.8;\
    }\
    \
    box {\
        background-color: rgba(255, 255, 255, 0.95);\
        border-radius: 15px;\
        padding: 20px;\
        margin: 12px;\
        box-shadow: 0 8px 32px rgba(170, 170, 170, 0.15);\
    }\
    \
    entry {\
        background-color: rgba(255, 255, 255, 0.9);\
        color: #333333;\
        border: 2px solid #ffd6d6;\
        border-radius: 10px;\
        padding: 12px 15px;\
        font-size: 16px;\
        transition: all 0.3s ease;\
    }\
    \
    entry:focus {\
        border-color: #ff9ecd;\
        box-shadow: 0 0 10px rgba(255, 158, 205, 0.2);\
    }\
    \
    .login-window button {\
        background-image: linear-gradient(45deg, #ff9a9e 0%, #fad0c4 99%);\
        color: #4a4a4a;\
        font-weight: bold;\
        border-radius: 12px;\
        padding: 12px 24px;\
        transition: all 0.3s ease;\
    }\
    \
    .login-window button:hover {\
        background-image: linear-gradient(45deg, #fad0c4 0%, #ff9a9e 99%);\
        transform: translateY(-2px);\
        box-shadow: 0 6px 20px rgba(0, 0, 0, 0.15);\
    }\
    \
    .save-button {\
        background-image: linear-gradient(45deg, #ff7eb3 0%, #ff758c 100%);\
    }\
    \
    .save-button:hover {\
        background-image: linear-gradient(45deg, #ff758c 0%, #ff7eb3 100%);\
    }\
    \
    .show-button {\
        background-image: linear-gradient(45deg, #7f7fd5 0%, #86a8e7 50%, #91eae4 100%);\
    }\
    \
    .show-button:hover {\
        background-image: linear-gradient(45deg, #91eae4 0%, #86a8e7 50%, #7f7fd5 100%);\
    }\
    \
    .logout-button {\
        background-image: linear-gradient(45deg, #f857a6 0%, #ff5858 100%);\
    }\
    \
    .logout-button:hover {\
        background-image: linear-gradient(45deg, #ff5858 0%, #f857a6 100%);\
    }\
    \
    .back-button {\
        background-image: linear-gradient(45deg, #4facfe 0%, #00f2fe 100%);\
    }\
    \
    .back-button:hover {\
        background-image: linear-gradient(45deg, #00f2fe 0%, #4facfe 100%);\
    }";
// Function to apply CSS
void apply_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}
// Function to validate username
int validate_username(const char *username) {
    if (!username || strlen(username) == 0 || strlen(username) >= MAX_USERNAME_LENGTH) {
        return 0;
    }
    
    for (int i = 0; username[i]; i++) {
        if (!isalnum(username[i]) && username[i] != '_') {
            return 0;
        }
    }
    return 1;
}

// Function to validate password
int validate_password(const char *password) {
    if (!password || strlen(password) < MIN_PASSWORD_LENGTH || 
        strlen(password) >= MAX_PASSWORD_LENGTH) {
        return 0;
    }
    
    int has_upper = 0, has_lower = 0, has_digit = 0;
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) has_upper = 1;
        if (islower(password[i])) has_lower = 1;
        if (isdigit(password[i])) has_digit = 1;
    }
    return has_upper && has_lower && has_digit;
}

// Function to safely create and check file
void check_or_create_file(const char *filename) {
    if (strlen(filename) >= MAX_FILENAME_LENGTH) {
        g_print("Error: Filename too long\n");
        return;
    }
    
    FILE *file = fopen(filename, "a");
    if (file) {
        chmod(filename, S_IRUSR | S_IWUSR);
        fclose(file);
    } else {
        g_print("Error: Cannot create file %s\n", filename);
    }
}

// Function to verify login credentials
int login_user(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        g_print("Error: Cannot open users file.\n");
        return 0;
    }
    
    char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2];
    char stored_username[MAX_USERNAME_LENGTH], stored_password[MAX_PASSWORD_LENGTH];
    int found = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%49s %49s", stored_username, stored_password) == 2) {
            if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
                found = 1;
                break;
            }
        }
    }
    
    fclose(file);
    return found;
}

// Function to handle login action
void handle_login(GtkWidget *widget, gpointer data) {
    const char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    g_print("Login attempt for user: %s\n", username);

    if (!validate_username(username) || !validate_password(password)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(login_window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Invalid username or password format.\nPassword must be at least 8 characters with uppercase, lowercase, and numbers.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    int login_result = login_user(username, password);
    g_print("Login result: %d\n", login_result);
    if (login_result == 1) {
        strncpy(current_user, username, MAX_USERNAME_LENGTH - 1);
        current_user[MAX_USERNAME_LENGTH - 1] = '\0';
        gtk_widget_destroy(login_window);
        open_diary(NULL, NULL);  // Open the diary window on successful login
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(login_window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Invalid username or password.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

// Function to register a new user
int register_user(const char *username, const char *password) {
    if (!validate_username(username) || !validate_password(password)) {
        return -1; // Invalid format
    }

    FILE *check_file = fopen("users.txt", "r");
    if (check_file) {
        char stored_username[MAX_USERNAME_LENGTH], stored_password[MAX_PASSWORD_LENGTH];
        while (fscanf(check_file, "%49s %49s", stored_username, stored_password) == 2) {
            if (strcmp(username, stored_username) == 0) {
                fclose(check_file);
                return 0; // Username exists
            }
        }
        fclose(check_file);
    }

    FILE *file = fopen("users.txt", "a");
    if (!file) {
        return 0;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    chmod("users.txt", S_IRUSR | S_IWUSR);

    char filename[MAX_FILENAME_LENGTH];
    snprintf(filename, MAX_FILENAME_LENGTH, "%s_diary.txt", username);
    check_or_create_file(filename);

    return 1;
}

// Function to handle registration action
void handle_register(GtkWidget *widget, gpointer data) {
    const char *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    int result = register_user(username, password);
    if (result == 1) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(login_window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Registration successful! You can now login.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else if (result == -1) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(login_window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Invalid username or password format.\nPassword must be at least 8 characters with uppercase, lowercase, and numbers.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(login_window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Registration failed. Username may already exist.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

// Function to delete user data (logout)
void delete_user_data(const char *username) {
    // Remove the user's diary file
    char filename[MAX_FILENAME_LENGTH];
    snprintf(filename, MAX_FILENAME_LENGTH, "%s_diary.txt", username);
    remove(filename);

    // Remove the username and password from the users file
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        g_print("Error: Cannot open users file for deletion.\n");
        return;
    }

    char temp_filename[] = "users_temp.txt";
    FILE *temp_file = fopen(temp_filename, "w");
    if (!temp_file) {
        fclose(file);
        g_print("Error: Cannot open temporary file for deletion.\n");
        return;
    }

    char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2];
    char stored_username[MAX_USERNAME_LENGTH], stored_password[MAX_PASSWORD_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%49s %49s", stored_username, stored_password) == 2) {
            if (strcmp(username, stored_username) != 0) {
                fprintf(temp_file, "%s %s\n", stored_username, stored_password);
            }
        }
    }

    fclose(file);
    fclose(temp_file);
    remove("users.txt");
    rename(temp_filename, "users.txt");

    g_print("User data deleted successfully.\n");
}

// Function to save a diary entry
void save_entry(GtkWidget *widget, gpointer text_view) {
    if (strlen(current_user) == 0) {
        g_print("Error: No user logged in.\n");
        return;
    }

    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    gchar *text;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    if (!text || strlen(text) == 0) {
        GtkWidget *parent_window = gtk_widget_get_toplevel(widget);
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent_window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Diary entry cannot be empty.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        g_free(text);
        return;
    }

    char filename[MAX_FILENAME_LENGTH];
    if (snprintf(filename, MAX_FILENAME_LENGTH, "%s_diary.txt", current_user) >= MAX_FILENAME_LENGTH) {
        g_print("Error: Filename too long.\n");
        g_free(text);
        return;
    }

    FILE *file = fopen(filename, "a");
    if (!file) {
        g_print("Error: Could not open diary file.\n");
        g_free(text);
        return;
    }

    time_t now = time(NULL);
    char *date = ctime(&now);
    if (date) {
        date[strcspn(date, "\n")] = '\0';
        fprintf(file, "\n--- Entry: %s\n%s\n", date, text);
    }

    fclose(file);
    chmod(filename, S_IRUSR | S_IWUSR);

    g_print("Entry saved successfully for user: %s\n", current_user);
    gtk_text_buffer_set_text(buffer, "", -1);
    g_free(text);
}

// Function to show saved diary entries
void show_entries(GtkWidget *widget, gpointer window) {
    if (strlen(current_user) == 0) {
        g_print("Error: No user logged in.\n");
        return;
    }

    char filename[MAX_FILENAME_LENGTH];
    snprintf(filename, MAX_FILENAME_LENGTH, "%s_diary.txt", current_user);

    FILE *file = fopen(filename, "r");
    if (!file) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "No entries found.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Create a dialog to display entries with increased size
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Diary Entries",
        GTK_WINDOW(window),
        GTK_DIALOG_MODAL,
        "Close",
        GTK_RESPONSE_CLOSE,
        NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 800, 600);  // Set dialog size

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_window, 600, 400);
    
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    
    // Read and display the content
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    char *content = NULL;
    size_t content_size = 0;
    size_t buffer_size = 1024;
    size_t read_size;

    content = malloc(buffer_size);
    if (!content) {
        fclose(file);
        gtk_widget_destroy(dialog);
        return;
    }

    while ((read_size = fread(content + content_size, 1, buffer_size, file)) > 0) {
        content_size += read_size;
        if (read_size < buffer_size) break;

        char *new_content = realloc(content, content_size + buffer_size);
        if (!new_content) {
            g_free(content);
            fclose(file);
            gtk_widget_destroy(dialog);
            return;
        }
        content = new_content;
    }

    fclose(file);

    // Set the text in the text view
    gtk_text_buffer_set_text(buffer, content, content_size);
    free(content);

    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),
                       scrolled_window, TRUE, TRUE, 0);
    
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
//handle_logout function with confirmation dialog
void handle_logout(GtkWidget *widget, gpointer diary_window) {
    if (strlen(current_user) == 0) {
        g_print("Error: No user logged in.\n");
        return;
    }

    // Create confirmation dialog
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(diary_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_WARNING,
        GTK_BUTTONS_OK_CANCEL,
        "Warning: Logging out will delete all your saved information!\n\nDo you want to proceed?");
    
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    if (response == GTK_RESPONSE_OK) {
        // Delete user data on logout
        delete_user_data(current_user);

        // Clear the current user
        memset(current_user, 0, sizeof(current_user));

        g_signal_handlers_disconnect_by_func(diary_window, G_CALLBACK(gtk_main_quit), NULL);


        // Destroy the diary window
        gtk_widget_destroy(GTK_WIDGET(diary_window));

        // Create and show new login window
        create_login_window();
        
        g_print("User logged out successfully.\n");
    }
    // If response is CANCEL, do nothing and return to diary window
}

//create_login_window with styling
void create_login_window() {
    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(login_window), "Diary Login");
    gtk_window_set_default_size(GTK_WINDOW(login_window), 500, 300);
    gtk_style_context_add_class(gtk_widget_get_style_context(login_window), "login-window");
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 20);

    // Add a welcome label
    GtkWidget *welcome_label = gtk_label_new("Welcome to Your Digital Diary");
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_scale_new(1.5);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(welcome_label), attr_list);
    pango_attr_list_unref(attr_list);

    GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *password_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    username_entry = gtk_entry_new();
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

    GtkWidget *username_label = gtk_label_new("Username:");
    GtkWidget *password_label = gtk_label_new("Password:");

    gtk_widget_set_size_request(username_entry, 300, 40);
    gtk_widget_set_size_request(password_entry, 300, 40);

    gtk_box_pack_start(GTK_BOX(username_box), username_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(username_box), username_entry, TRUE, TRUE, 10);

    gtk_box_pack_start(GTK_BOX(password_box), password_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(password_box), password_entry, TRUE, TRUE, 10);

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    GtkWidget *login_button = gtk_button_new_with_label("Login");
    GtkWidget *register_button = gtk_button_new_with_label("Register");

    gtk_widget_set_size_request(login_button, 150, 40);
    gtk_widget_set_size_request(register_button, 150, 40);

    gtk_box_pack_start(GTK_BOX(button_box), login_button, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(button_box), register_button, TRUE, TRUE, 10);

    g_signal_connect(login_button, "clicked", G_CALLBACK(handle_login), NULL);
    g_signal_connect(register_button, "clicked", G_CALLBACK(handle_register), NULL);

    gtk_box_pack_start(GTK_BOX(main_box), welcome_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(main_box), username_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(main_box), password_box, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 20);

    gtk_container_add(GTK_CONTAINER(login_window), main_box);
    gtk_widget_show_all(login_window);
}

//open_diary with styling
void open_diary(GtkWidget *widget, gpointer data) {
    GtkWidget *diary_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(diary_window), "My Digital Diary");
    gtk_window_set_default_size(GTK_WINDOW(diary_window), 800, 600);
    gtk_style_context_add_class(gtk_widget_get_style_context(diary_window), "diary-window");

    // Only quit when explicitly logging out or closing the window with the X button
    g_signal_connect(diary_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_widget_set_size_request(scrolled_window, 780, 450);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // Create buttons with style classes
    GtkWidget *save_button = gtk_button_new_with_label("Save Entry");
    GtkWidget *show_button = gtk_button_new_with_label("Show Entries");
    GtkWidget *logout_button = gtk_button_new_with_label("Logout");
    GtkWidget *back_button = gtk_button_new_with_label("Back to Login");

    // Add style classes to buttons
    gtk_style_context_add_class(gtk_widget_get_style_context(save_button), "save-button");
    gtk_style_context_add_class(gtk_widget_get_style_context(show_button), "show-button");
    gtk_style_context_add_class(gtk_widget_get_style_context(logout_button), "logout-button");
    gtk_style_context_add_class(gtk_widget_get_style_context(back_button), "back-button");

    gtk_widget_set_size_request(save_button, 150, 50);
    gtk_widget_set_size_request(show_button, 150, 50);
    gtk_widget_set_size_request(logout_button, 150, 50);
    gtk_widget_set_size_request(back_button, 150, 50);

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(button_box), save_button, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(button_box), show_button, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(button_box), back_button, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(button_box), logout_button, TRUE, TRUE, 10);

    g_signal_connect(save_button, "clicked", G_CALLBACK(save_entry), text_view);
    g_signal_connect(show_button, "clicked", G_CALLBACK(show_entries), diary_window);
    g_signal_connect(logout_button, "clicked", G_CALLBACK(handle_logout), diary_window);
    g_signal_connect(back_button, "clicked", G_CALLBACK(handle_back), diary_window);

    GtkWidget *content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 20);
    gtk_box_pack_start(GTK_BOX(content_area), scrolled_window, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(content_area), button_box, FALSE, FALSE, 0);

    // Add a welcome message with user name
    char welcome_text[100];
    snprintf(welcome_text, sizeof(welcome_text), "Welcome to your diary, %s!", current_user);
    GtkWidget *welcome_label = gtk_label_new(welcome_text);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_scale_new(1.5);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_attributes(GTK_LABEL(welcome_label), attr_list);
    pango_attr_list_unref(attr_list);
    
    gtk_box_pack_start(GTK_BOX(content_area), welcome_label, FALSE, FALSE, 0);
    gtk_box_reorder_child(GTK_BOX(content_area), welcome_label, 0);

    gtk_container_add(GTK_CONTAINER(diary_window), content_area);
    gtk_widget_show_all(diary_window);
}

//main function
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    apply_css();  // Apply the CSS styling
    create_login_window();
    gtk_main();
    return 0;
}