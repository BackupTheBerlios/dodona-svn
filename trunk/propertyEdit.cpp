#include "VLG.h"

void pEdit(VLGbase* w) {
	GtkWidget *dialog, *label, *clickedEvent,*textProp;
	
	dialog = gtk_dialog_new_with_buttons ("Properties",
											(GtkWindow*)w->parent->widget,
											GTK_DIALOG_MODAL,
											GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
											GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT,
											NULL);

 	label = gtk_label_new ("Clicked Event");
	
//clickedScript
	clickedEvent=gtk_entry_new();	
	gtk_entry_set_text(GTK_ENTRY(clickedEvent),w->clickedScript);

	textProp=gtk_entry_new();
	char str[1024];	
	sprintf(&str[0],"%s",w->initialtext);
	gtk_entry_set_text(GTK_ENTRY(textProp),str);

	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),label);	
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),clickedEvent);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),textProp);
	gtk_widget_show_all (dialog);
	
	gint result = gtk_dialog_run (GTK_DIALOG (dialog));

	switch (result)
	{
		case GTK_RESPONSE_ACCEPT:
			sprintf(&w->clickedScript[0],"%s",gtk_entry_get_text(GTK_ENTRY(clickedEvent)));
			
			sprintf(&str[0],"%s",gtk_entry_get_text(GTK_ENTRY(textProp)));
			w->setText(str);
			w->setInitText(str);

			break;
		default:
			printf("Canceled\n");
			break;
	}
	gtk_widget_destroy (dialog);
}
