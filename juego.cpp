#include <iostream>
#include<allegro5/allegro.h>
#include<stdlib.h>
#include<string.h>
#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
#include<string>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<Windows.h>
#include<sstream>
#include<ctime>
#include<stdio.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "FS_libreria.h"

using namespace std;
 
void salir();
void jugar(ALLEGRO_DISPLAY* ventana);
void menu(ALLEGRO_DISPLAY* ventana);
//void impNum(int n1, int n2); 
int puntaje(int resultado, int avanceJugador, int puntos);
void usarTeclado(ALLEGRO_DISPLAY* ventana);
float ancho = 1106;
float alto = 700;

ALLEGRO_BITMAP* buffer;
ALLEGRO_FONT* Golden_Age_Shad = al_load_font("fuentes/Golden_Age_Shad.otf", 70, 0);
ALLEGRO_FONT* Golden_Age_Shad_pequeño;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_COLOR blanco;
ALLEGRO_COLOR naranja;
ALLEGRO_COLOR negro;
ALLEGRO_COLOR rojo;
ALLEGRO_COLOR azul;
ALLEGRO_KEYBOARD_STATE keyState;

int main()
{
	srand (time(NULL));
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR:404", "No se pudo cargar correctamente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_image_addon();
	al_install_keyboard();

	// V E N T A N A
	ALLEGRO_DISPLAY* ventana = al_create_display(ancho, alto);
	ALLEGRO_BITMAP* buffer = al_create_bitmap(ancho, alto);
	Golden_Age_Shad = al_load_font("fuentes/Golden_Age_Shad.otf", 70, 0);
	Golden_Age_Shad_pequeño = al_load_font("fuentes/Golden_Age_Shad.otf", 30, 0);

	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);
	al_set_window_title(ventana, "CONTEMOS");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);

	//Q U E U E
	queue = al_create_event_queue();

	//C O L O R E S
	blanco = al_map_rgb(255, 255, 255);
	naranja = al_map_rgb(239, 186, 36);
	negro = al_map_rgb(0, 0, 0);

	al_register_event_source(queue, al_get_mouse_event_source());

	menu(ventana);
	
}

void menu(ALLEGRO_DISPLAY*ventana)
{
	ALLEGRO_BITMAP* menu_null = al_load_bitmap("imagenes/fondo/background.png");
	ALLEGRO_BITMAP* menu_start = al_load_bitmap("imagenes/fondo/background_jugar.png");
	ALLEGRO_BITMAP* menu_start_1 = al_load_bitmap("imagenes/fondo/background_jugar_1.png");
	ALLEGRO_BITMAP* menu_exit = al_load_bitmap("imagenes/fondo/background_salir.png");
	ALLEGRO_BITMAP* menu_exit_1 = al_load_bitmap("imagenes/fondo/background_salir_1.png");
	ALLEGRO_BITMAP* buffer = al_load_bitmap("fondo1.png");
	ALLEGRO_BITMAP* tutorial_null = al_load_bitmap("fondo/tutorial/1.png");
	ALLEGRO_BITMAP* tutorial_1 = al_load_bitmap("fondo/tutorial/2.png");
	ALLEGRO_BITMAP* tutorial_2 = al_load_bitmap("fondo/tutorial/3.png");
	blanco = al_map_rgb(255, 255, 255);
	naranja = al_map_rgb(239, 186, 36);
	negro = al_map_rgb(0, 0, 0);
	rojo = al_map_rgb(255, 43, 43);
	azul = al_map_rgb(53, 43, 255);

	bool end_program = false;
	bool tutorial = false;

	int x = -1, y = -1;
	int segundo = 0;
	while (!end_program)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);



		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && !tutorial)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 704 && x <= 976 && y >= 398 && y <= 475)
			{
				al_draw_bitmap(menu_start_1, 0, 0, 0);
				if (evento.mouse.button & 1)
				{
					al_draw_bitmap(menu_start, 0, 0, 0);
					tutorial = true;
					//jugar(ventana);
				}
				else
				{
					al_draw_bitmap(menu_start_1, 0, 0, 0);
				}
			}
			else
			{
				if (x >= 704 && x <= 976 && y >= 529 && y <= 607)
				{
					al_draw_bitmap(menu_exit_1, 0, 0, 0);
					if (evento.mouse.button & 1)
					{
						al_draw_bitmap(menu_exit, 0, 0, 0);
						cout << "Presionaste SALIR\n";
						end_program = true;
					}
					else
					{
						al_draw_bitmap(menu_exit_1, 0, 0, 0);
					}
				}
				else
				{
					al_draw_bitmap(menu_null, 0, 0, 0);
				}
			}
		}
		else
		{
			al_draw_bitmap(menu_null, 0, 0, 0);
		}

		if (tutorial)
		{
			al_draw_bitmap(tutorial_null, 0, 0, 0);
			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				x = evento.mouse.x;
				y = evento.mouse.y;
				if (evento.mouse.button & 1)
				{
					printf("x: %d y: %d\n", x, y);
				}
			}
		}

		al_flip_display();
	}

}

void salir()
{
	while (true)
	{
		ALLEGRO_EVENT evento;
		queue = al_create_event_queue();
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);
		al_flip_display();

	}
	cout << "diste click en salir";
}

void jugar(ALLEGRO_DISPLAY * ventana)
{
	cout << "Presionaste JUGAR\n";
	buffer = al_load_bitmap("fondo/tutorial.png");
	ALLEGRO_BITMAP * btn_1_activo = al_load_bitmap("Botones/b1_flecha.png");
	ALLEGRO_BITMAP* btn_2_seleccion = al_load_bitmap("Botones/b2_flecha.png");
	ALLEGRO_BITMAP* btn_3_seleccion = al_load_bitmap("Botones/b1_5_flecha.png");

	ALLEGRO_EVENT evento;
	al_wait_for_event(queue, &evento);
	
	int x = -1, y = -1;

		al_draw_bitmap(buffer, 0, 0, 0);
		al_draw_bitmap(btn_1_activo, 808, 501, 0);

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 804 && x <= 928 && y >= 496 && y <= 579)
			{
				al_draw_bitmap(btn_2_seleccion, 808, 501, 0);
				if (evento.mouse.button & 1)
				{
					al_draw_bitmap(btn_3_seleccion, 808, 501, 0);
					jugar(ventana);
				}
			}
		}
		/*while (true)
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(queue, &evento);
			al_clear_to_color(negro);
			al_flip_display();
			usarTeclado(ventana);
		}*/

}

void usarTeclado(ALLEGRO_DISPLAY* ventana)
{

	//para que se ejecute a la misma velocidad en cualquier computadora 
	ALLEGRO_TIMER* tiempo = al_create_timer(1.0 / 5);
	ALLEGRO_EVENT_QUEUE* evento_queue = al_create_event_queue();
	ALLEGRO_BITMAP* caminando[8];
	ALLEGRO_BITMAP* fondo[2];
	ALLEGRO_BITMAP* vidas[7];
	ALLEGRO_KEYBOARD_STATE keyState;

	al_register_event_source(evento_queue, al_get_keyboard_event_source());
	al_register_event_source(evento_queue, al_get_timer_event_source(tiempo));
	al_get_keyboard_state(&keyState);
	//no declarar variables antes del tiempo
	al_start_timer(tiempo);

	bool terminado = false, dibujo = true, activo = false;
	int x = 60, y = 460;
	int xfondo = 60;
	int velMovimiento = 200;
	int i, j, l, indice, resultado, avanceJugador, puntos = 0;
	indice = 0, j = 0, avanceJugador = 1;
	bool correcto = true;
	float camaraPos[2] = { 0,0 };
	int n1, n2;
	int rf = 5;
	n1 = 1;
	n2 = rand() % rf + 1;
	resultado = n1 + n2;
	//impNum(n1,n2); 

	//cargar imagenes
	for (i = 0; i < 8; i++)
	{
		std::stringstream str;
		str << "sprites/" << i + 1 << ".png";
		caminando[i] = al_load_bitmap(str.str().c_str());
	}
	for (j = 0; j < 2; j++)
	{
		std::stringstream str;
		str << "fondo/" << j + 1 << ".png";
		fondo[j] = al_load_bitmap(str.str().c_str());
	}
	for (l = 0; l <= 7; l++)
	{
		std::stringstream str;
		str << "lifes/" << l << ".png";
		vidas[l] = al_load_bitmap(str.str().c_str());
	}
	j = 0;
	l = 7;

	while (!terminado)
	{
		ALLEGRO_EVENT eventos;
		al_wait_for_event(evento_queue, &eventos);
		if (eventos.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (eventos.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:
				x += velMovimiento;
				avanceJugador++;
				xfondo += velMovimiento;

				if (x >= 1060)
				{
					x = 60;
				}
				if (xfondo < 1060)
				{
					j = 0;
				}
				else
				{
					j = 1;
					if (xfondo > 2120)
					{
						j = 0;
						xfondo = 60;

					}
				}

				break;
			case ALLEGRO_KEY_LEFT:
				
				if (avanceJugador > 1)
				{
					avanceJugador--;
					x -= velMovimiento;
				}
				break;
			case ALLEGRO_KEY_ENTER:
				puntos = puntaje(resultado, avanceJugador, puntos);	
				correcto = respuesta(resultado, avanceJugador); 
				if (!correcto)
				{
					x = 60;
					puntos = 0;
					avanceJugador = 1;
					n1 = 1;
					n2 = rand() % rf + 1;
					l--;
					if (l == 0)
					{
						terminado = true; 
					}
				}
				else
				{
					n1 = resultado;
					avanceJugador = resultado;
					n2 = rand() % rf + 1;
					
				}
				resultado = n1 + n2;
				//terminado = true;
				break;
			}
		}

		if (eventos.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			terminado = true;
		}
		else
		{
			if (eventos.type == ALLEGRO_EVENT_TIMER)
			{
				activo = true;
				if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
				{
					x += velMovimiento;
				}
				if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
				{
					x -= velMovimiento;
				}
				/*if (al_key_down(&keyState, ALLEGRO_KEY_ENTER))
				{
					puntos = puntaje(resultado, avanceJugador, puntos);
				}*/
			}
			else
			{
				activo = false;
			}

			if (activo)
			{
				indice++;
				if (indice >= 8)
				{
					indice = 0;
				}
			}
			dibujo = true;

		}
		if (dibujo)
		{
			al_draw_bitmap(fondo[j], 0, 0, 0);
			//impNum(n1, n2);
			al_draw_text(Golden_Age_Shad, azul, 256, 311, NULL, (to_string(n1)).c_str());
			al_draw_text(Golden_Age_Shad, azul, 530, 311, NULL, (to_string(n2)).c_str());
			//mensajes(avanceJugador, puntos); 
			al_draw_text(Golden_Age_Shad_pequeño, rojo, 200, 410, NULL, "ESTAS EN EL");
			al_draw_text(Golden_Age_Shad_pequeño, rojo, 480, 410, NULL, "AVANZA");
			al_draw_text(Golden_Age_Shad_pequeño, rojo, 742, 410, NULL, "LlEGASTE A");
			al_draw_text(Golden_Age_Shad, azul, 812, 311, NULL, (to_string(avanceJugador)).c_str());
			al_draw_text(Golden_Age_Shad, rojo, 70, 49, NULL, (to_string(puntos)).c_str());
			al_draw_bitmap(caminando[indice], x, y, NULL);
			al_draw_bitmap(vidas[l], 500, 74, NULL);
			al_flip_display();

		}
	}
	
	for (i = 0; i < 8; i++)
	{
		al_destroy_bitmap(caminando[i]);
	}
	al_destroy_event_queue(evento_queue);
	al_destroy_bitmap(fondo[j]);
	al_destroy_display(ventana);
}


