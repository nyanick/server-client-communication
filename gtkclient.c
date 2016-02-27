#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void destroy (GtkWidget *window, gpointer data);
static void cal(GtkWidget *button, gpointer data);

GtkWidget *window,*hbox, *vbox1, *vbox2, *button_cal, *label1, *label2, *label13;
GtkWidget *label3, *label4, *label5, *label6, *label7, *label8, *hbox1,*hbox2,*hbox3;
GtkWidget *input1_entry, *result_entry, *input2_entry, *op_entry;
GtkWidget *label9, *label10, *label11, *label12,*hbox4,*hbox5,*hbox6;
double num1,num2,sum;char *operand;
int op;char answer[4];const gchar *sms;
int sockfd,result,len;
struct sockaddr_in address;

int main( int argc, char *argv[])
{
	
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "client");
	gtk_window_set_default_size(GTK_WINDOW(window),400,100);
	
	label1 = gtk_label_new("A Simple Client-Server communication");
	label2 = gtk_label_new("input");
	label3 = gtk_label_new("Result from server");
	label4 = gtk_label_new("num1");
	label5 = gtk_label_new("operation");
	label6 = gtk_label_new("num2");
	label7 = gtk_label_new("");
	label8 = gtk_label_new("");
	label9 = gtk_label_new("");
	label10 = gtk_label_new("");
	label11 = gtk_label_new("");
	label12 = gtk_label_new("");
	label13 = gtk_label_new("");
	
	input1_entry = gtk_entry_new();
	input2_entry = gtk_entry_new();
	op_entry = gtk_entry_new();
	result_entry = gtk_entry_new();
	
	button_cal = gtk_button_new_with_label("Go");
		
	hbox = gtk_hbox_new(0,0);
	hbox1 = gtk_hbox_new(1,0);
	hbox2 = gtk_hbox_new(1,0);
	hbox4 = gtk_hbox_new(1,0);
	hbox5 = gtk_hbox_new(1,0);
	hbox6 = gtk_hbox_new(1,0);
	vbox1 = gtk_vbox_new(1,0);
	//resizing some widgets elements
	gtk_widget_set_size_request(button_cal, 50,40);
	gtk_widget_set_size_request(input1_entry,30,30);
	gtk_widget_set_size_request(op_entry,30,30);
	gtk_widget_set_size_request(input2_entry,30,30);
	gtk_widget_set_size_request(result_entry,60,50);

	//start packing my boxes from small to large
	gtk_box_pack_start(GTK_BOX(hbox1),label2,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox1),input1_entry,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox1),op_entry,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox1),input2_entry,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox1),input2_entry,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox1),button_cal,TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox2),label9,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox2),label4,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox2),label5,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox2),label6,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox2),label10,TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(hbox5),label3,TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox5),result_entry,TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox5),label12,TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1),label1,TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1),hbox2,FALSE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1),hbox1,FALSE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1),hbox5,TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox1),label7,TRUE, FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox),vbox1,TRUE, TRUE,0);
	
	
	//my callback signals
	g_signal_connect(GTK_OBJECT(window), "destroy",GTK_SIGNAL_FUNC(destroy),NULL);
	g_signal_connect(GTK_OBJECT(button_cal), "clicked",GTK_SIGNAL_FUNC(cal),NULL);	
	
	
	gtk_container_add(GTK_CONTAINER(window), hbox);
	gtk_widget_show_all(vbox1);
    gtk_widget_show_all(hbox);
    gtk_widget_show_all(hbox1);
    gtk_widget_show_all(hbox2);
    gtk_widget_show_all(hbox5);
	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}

static void destroy (GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

static void cal(GtkWidget *button, gpointer data)
{
	
	
	num1 = atof(gtk_entry_get_text(GTK_ENTRY(input1_entry)));
	num2 = atof(gtk_entry_get_text(GTK_ENTRY(input2_entry)));
	operand = gtk_entry_get_text(GTK_ENTRY(op_entry));
	op = operand[0];
	printf("%f %c %f\n",num1,op,num2);

	//my client code from c
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9734);
	len = sizeof(address);
	
	result = connect(sockfd, (struct sockaddr *) &address, len);
	
	if(result == -1)
	{
		gtk_entry_set_text(GTK_ENTRY(result_entry),"an error occur in the connection\n");
		exit(1);
	}
	
	write(sockfd, &num1, 8);
	write(sockfd, &num2, 8);
	write(sockfd, &op, 1);
		
	read(sockfd, &sum, 8);
	
	sprintf(answer,"%g",sum);
	gtk_entry_set_text(GTK_ENTRY(result_entry),(gchar*)answer);
	close(sockfd);
	
	
	
}

