#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include<stdbool.h>

#define WINDOW_WIDTH 1870      // largeur de la fenêtre pour afficher le piano 
#define WINDOW_HEIGHT 400		// hauteur de la fenêtre pour afficher le piano
#define N 10
	//gcc main.c -o prog $(sdl2-config --cflags --libs)
	// SDL_Renderer_SOFTWARE
	//SDL_Renderer_ACCELERATED
	//SDL_Renderer_PRESENTVSYNC
	//SDL_Renderer_TARGETTEXTURE

void SDL_ExitWithError(const char *message);
int touche_blanche(int touche);
void colorier_piano(SDL_Renderer *renderer, int touche,SDL_Texture *texture);

int main(int argc, char **argv){
	SDL_Window *window=NULL;     // Création et initialisation de la fenêtre 
	SDL_Renderer *renderer=NULL ;	// Création et initialisation du rendu 
	int *nombres_de_touches; 		// Nombre de touches du morceau musique 
	int touches[N]={0,5,9,82,52,63,34,65,25,46};
	//SDL_Renderer *renderer_tmp=NULL ;

	if(SDL_Init(SDL_INIT_VIDEO)!=0)     // On vérifie que l'on a bien pu initialisé la vidéo

	{
		SDL_ExitWithError("Initialisation SDL");
	}
	//Création de la fenêtre ainsi que du rendu 
	if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT,0,&window,&renderer)!=0){
		SDL_ExitWithError("Création de la fenêtre et du rendu échouée");
	}
	//SDL_CreateRenderer(&window,-1,0);
	
	SDL_Surface *image=NULL;  // création et initialisation de la surface qui va accueillir l'image 
	SDL_Texture *texture=NULL;		//création et initialisation de la texture 
	
	image=SDL_LoadBMP("pianof.bmp");      // Chargement du piano sur la surface
	
	// On vérifie que l'on a pu charger l'image et le cas contraire on détruit la fenêtre et le rendu.
	if (image==NULL){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de charger l'image");
	}

	texture=SDL_CreateTextureFromSurface(renderer,image); // On crée la texture à partir de l'image du tableau
	SDL_Texture *texture_tmp=SDL_CreateTextureFromSurface(renderer,image);


	//SDL_FreeSurface(image); // On libère la surface car elle ne nous est plus utile.

	// On vérifie qu'on a bien pu charger la texture et le cas contraire on ferme le rendu et la fenêtre.
	if (texture==NULL){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de charger la texture");

	}
	SDL_Rect rectangle; //  Création d'un rectangle
	if(SDL_QueryTexture(texture, NULL, NULL ,&rectangle.w, &rectangle.h)!=0 ){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de charger la texture");

	}
	rectangle.x=(WINDOW_WIDTH-rectangle.w)/2;    //On centre l'image du piano
	rectangle.y=(WINDOW_HEIGHT-rectangle.h)/2;


	if(SDL_RenderCopy(renderer,texture, NULL,&rectangle)!=0){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de charger la texture");

	}
	for(int j=0;j<=N-1;j++){
		SDL_Texture *texture_tmp=SDL_CreateTextureFromSurface(renderer,image);
		int touche_tmp=touches[j];
		colorier_piano(renderer,touche_tmp,texture);
		SDL_RenderPresent(renderer);
		SDL_Delay(400);
		rectangle.x=(WINDOW_WIDTH-rectangle.w)/2;    //On centre l'image du piano
		rectangle.y=(WINDOW_HEIGHT-rectangle.h)/2;
		SDL_QueryTexture(texture_tmp, NULL, NULL ,&rectangle.w, &rectangle.h);
		SDL_RenderCopy(renderer,texture_tmp, NULL,&rectangle);
		

		
		;
			

	}


	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_FreeSurface(image);

	SDL_DestroyTexture(texture);


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();


	
	return EXIT_SUCCESS;
}



void SDL_ExitWithError(const char *message){
	SDL_Log("ERREUR : %s > %s\n", message , SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);

}


// Fonction renvoyant un booléen indiquant si la touche est noire ou non .
bool touche_noire(int touche){
	if ((touche==2)||(touche==5)||(touche==7)||(touche==10)||(touche==12)||(touche==14)||(touche==17)||(touche==19)||(touche==22)||(touche==24)||(touche==26)||(touche==29)||(touche==31)||(touche==34)||(touche==36)||(touche==38)||(touche==41)||(touche==43)||(touche==46)||(touche==48)||(touche==50)||(touche==53)||(touche==55)||(touche==58)||(touche==60)||(touche==62)||(touche==65)||(touche==67)||(touche==70)||(touche==72)||(touche==74)||(touche==77)||(touche==79)||(touche==82)||(touche==84)||(touche==86)){
		return true;		
	}
	return false;
}

// Fonction qui permet de colorier en rouge les touches jouées sur le piano
void colorier_piano(SDL_Renderer *renderer, int touche,SDL_Texture *texture){
	//On regarde si la touche jouée est une touche noire 
	SDL_SetRenderTarget(renderer,texture); 
	if(touche_noire(touche)){
		SDL_Color rouge={255,1,1,255}; // Structure représentant la couleur rouge
		SDL_SetRenderDrawColor(renderer, rouge.r, rouge.g, rouge.b, rouge.a);     // Initialise la couleur à rouge pour le dessin sur le rendu 
		SDL_Rect rect={21*touche+1,22,26,256};    // Défini le rectangle à colorier en rouge 
		SDL_RenderFillRect(renderer,&rect);			// Colorie en rouge le rectangle en questioon 
	}
	//On fait la même chose pour une touche blanche 
	else{
		int touche_b=touche_blanche(touche);
		SDL_Color rouge={255,1,1,255};
		SDL_SetRenderDrawColor(renderer, rouge.r, rouge.g, rouge.b, rouge.a);
		SDL_Rect rect={21.9+(35.1)*touche_b,279,33.9,102};
		SDL_RenderFillRect(renderer,&rect);

	}
	SDL_SetRenderTarget(renderer,NULL);


}

int touche_blanche(int touche){
	int touche_blanche;
	if (touche==1){
		touche_blanche=touche;
	}
	if (touche==3){
		touche_blanche=touche-1;
	}
	if (touche=88){
		touche_blanche=52;
	}
	int octave=touche/12;
	int place=touche%12;
	if (place==0){
		touche_blanche=touche-1-6*octave;
	}
	if(place==2){
		touche_blanche=touche-2-6*octave;
	}
	if((place==4)||(place==5)){
		touche_blanche=touche-3-6*octave;
	}
	if(place==7){
		touche_blanche=touche-4-6*octave;
	}
	if(place==9){
		touche_blanche=touche-5-6*octave;
	}
	if(place==11){
		touche_blanche=touche-6*(octave+1);
	}





}
