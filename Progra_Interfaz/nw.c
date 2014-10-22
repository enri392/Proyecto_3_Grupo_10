#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <unistd.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <pthread.h>

int x=0;
int y=471;
int m=0;
int f=1;
int mx=0;
int my=0;
GtkWidget *nom,*puntaje;

void salir(){
;
}

void reset(){
;
}

void jugar(){
	;//char nombre[10];
	//char l[10];
	//sscanf(gtk_entry_get_text(GTK_ENTRY(nom)), "%s",nombre);
	//sprintf(l, "%s", nombre);
	//gtk_entry_set_text((GtkLabel *)puntaje, l);
}

static void do_drawing(cairo_t *);
static void do_drawing2(cairo_t *);

struct {
  gushort count;
} t;

struct {
  double coordx;
  double coordy;
} glob;

struct {
  cairo_surface_t *image;  
} im;

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    f=0;
    gtk_main_quit ();
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{
  do_drawing(cr);

  return FALSE;
}

static gboolean on_draw_event2(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{
  do_drawing2(cr);

  return FALSE;
}

static void do_drawing2(cairo_t *cr)
{ 
  
  //cairo_set_source_surface(cr, im.image, 0, 0);
  //cairo_paint(cr);
  
  cairo_set_line_width(cr, 9);  
	cairo_set_source_rgb(cr, 0.69, 0.19, 0);

  	srand(time(NULL));
  
	cairo_arc(cr, mx, my, 50, 0, 2 * M_PI);
	cairo_stroke_preserve(cr);

  	cairo_set_source_rgb(cr, 0.3, 0.4, 0.6); 
  	cairo_fill(cr);
	mx=mx+1;
	my=my+1;
	}

static gboolean mouse(GtkWidget *widget)
{
  t.count += 1;

  gtk_widget_queue_draw(widget);
  
  return TRUE;
}

static void do_drawing(cairo_t *cr)
{ 
  cairo_set_source_surface(cr, im.image, 0, 0);
  cairo_paint(cr);
  
  if (m==1){
	cairo_set_line_width(cr, 9);  
  	cairo_set_source_rgb(cr, 0, 0, 0);

  	cairo_arc(cr, glob.coordx, glob.coordy, 100, 0, 2 * M_PI);
 	cairo_stroke_preserve(cr);

  	cairo_set_source_rgb(cr, 0, 0, 0); 
  	cairo_fill(cr);
	}
  
  else{
  
  srand(time(NULL));
  x = rand() %785;
  y = rand() %471;
  //variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;

  glob.coordx = x;
  glob.coordy = y;
  cairo_pattern_t *r2; 
  
  cairo_translate(cr, glob.coordx, glob.coordy);
  
  r2 = cairo_pattern_create_radial(0, 0, 5, 0, 0, 50);  
  cairo_pattern_add_color_stop_rgb(r2, 0, 0.1, 1, 0);
  cairo_pattern_add_color_stop_rgb(r2, 0.9, 0, 0, 0);
  cairo_set_source(cr, r2);
  cairo_arc(cr, 0, 0, 50, 0, M_PI * 2);
  cairo_fill(cr); 
         
	/*cairo_set_line_width(cr, 9);  
	cairo_set_source_rgb(cr, 0.69, 0.19, 0);

	glob.coordx = x;
	glob.coordy = y;
  
	cairo_arc(cr, glob.coordx, glob.coordy, 50, 0, 2 * M_PI);
	cairo_stroke_preserve(cr);

  	cairo_set_source_rgb(cr, 0.3, 0.4, 0.6); 
  	cairo_fill(cr);*/
	}  
  	m=0;  
}

static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
   if (event->button == 1) {
        if((glob.coordx+50 > event->x) & (glob.coordx-50 < event->x)&
		(glob.coordy+50 > event->y) & (glob.coordy-50 < event->y)){
		g_print ("YEAH\n");
		m=1;
		gtk_widget_queue_draw(widget);
	}
  }

    return TRUE;
}

static gboolean time_handler(GtkWidget *widget)
{
  t.count += 1;
  gtk_widget_queue_draw(widget);
  
  return TRUE;
}

void *juego(void *arg) 
{
  GtkWidget *window;
  GtkWidget *darea;
  t.count = 0;

  vent();

  im.image = cairo_image_surface_create_from_png("/home/enrique/Escritorio/prueba/Space.png");

  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), darea);
 
  gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event), NULL); 
  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event2), NULL); 

  g_signal_connect(window, "destroy",
      G_CALLBACK(destroy), NULL);  
    
  g_signal_connect(window, "button-press-event", 
      G_CALLBACK(clicked), NULL);
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 784, 470); 
  gtk_window_set_title(GTK_WINDOW(window), "Circles");
	
  g_timeout_add(10, (GSourceFunc) mouse, (gpointer) window);
  g_timeout_add(1000, (GSourceFunc) time_handler, (gpointer) window);
  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}

void vent(){

	GtkWidget *window;
	GtkWidget *descripcion[5];
	GtkWidget *layout;
	GtkWidget *button;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_window_set_title (GTK_WINDOW (window), "Progra");
	gtk_container_set_border_width (GTK_CONTAINER (window), 0);
	gtk_window_set_default_size (GTK_WINDOW(window), 300, 350);
	
	//Layout
	layout = gtk_layout_new(NULL,NULL);

	//Descripciones
	descripcion[0] = gtk_label_new("JUEGO");
	descripcion[1] = gtk_label_new("Nombre");
	descripcion[2] = gtk_label_new("");
	
	puntaje = gtk_label_new("Puntaje");

	//Campo de texto
	nom = gtk_entry_new();
	
	//Formato campos de texto
	gtk_entry_set_max_length(GTK_ENTRY(nom),10);

	//Tamaño campos de texto
	gtk_entry_set_width_chars(GTK_ENTRY(nom),15);

	//Boton
	button = gtk_button_new_with_label ("Salir");
	g_signal_connect (button, "clicked", G_CALLBACK (salir), NULL);
	button = gtk_button_new_with_label ("Reiniciar");
	g_signal_connect (button, "clicked", G_CALLBACK (reset), NULL);
	button = gtk_button_new_with_label ("Jugar");
	g_signal_connect (button, "clicked", G_CALLBACK (jugar), NULL);

	//Ensamblar objetos
	gtk_layout_put(GTK_LAYOUT(layout), descripcion[0], 10, 10);
	gtk_layout_put(GTK_LAYOUT(layout), descripcion[1], 10, 50);
	gtk_layout_put(GTK_LAYOUT(layout), descripcion[2], 30, 100);
	gtk_layout_put(GTK_LAYOUT(layout), puntaje, 10, 100);
	gtk_layout_put(GTK_LAYOUT(layout), nom, 100, 50);
	gtk_layout_put(GTK_LAYOUT(layout), button, 50, 150);

	gtk_container_add (GTK_CONTAINER (window), layout);

	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
  //pthread_t h1;
  pthread_t h2;

  gtk_init(&argc, &argv);

  //pthread_create(&h1,NULL,numero,NULL);
  pthread_create(&h2,NULL,juego,NULL);
  //pthread_join(h1,NULL);
  pthread_join(h2,NULL);

  return 0;
}

