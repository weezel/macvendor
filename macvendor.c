#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VALMISTAJAT "/home/weezel/ohjelmointi/c/macvendor/vendors.txt"

int isInLine( char *p, char *r );

int main( int argc, char **argv )
{
    FILE *input = NULL;
    /*char *vertailu;*/
    char etsittava[8];
    char valmistaja[256];
    int loytyi = 0;
    int i = 0;

    if( argc != 2 )
    {
        /* Ei saatu MAC-osoitetta parametrina */
        fprintf( stderr, "Give a mac address as a parameter.\n" );
        fprintf( stderr, "For example: macvendor 00-00-00\n");
        exit( 1 );
    }
    
    if( (input = fopen( VALMISTAJAT, "r" )) == NULL )
    {
        /* Valmistajien tietuetta ei saatu auki */
        fprintf( stderr, "Valmistajien tietuetta ei saatu auki.\n" );
        fprintf( stderr, "Varmista, että vendors.txt on samassa hakemistossa ohjelman kanssa.\n" );
        exit( 1 );
    }

    if( strlen( argv[1] ) < 8 )
    {
        fprintf( stderr, "Too short for a mac address.\n" );
        exit( 1 );
    }
    
    /* Siistitään mahdollisesti parametrina saatua väärää syntaksia */
    for( i = 0; i < 8; i++)
    {
        if( argv[1][i] == ':' )
            etsittava[i] = '-';
        else
            etsittava[i] = toupper( argv[1][i] );
    }
    
    /* Etsitään vastaavaa tietuetta tekstitiedostosta */
    while( fgets( valmistaja, sizeof( valmistaja ), input ) != NULL )
    {
        if( isInLine( etsittava, valmistaja ) == 1)
        {
            printf( "%s", valmistaja );
            loytyi = 1;
        }
    }
    fclose( input );
    
    if( loytyi == 0 )
    {
        fprintf( stderr, "Kyseistä valmistajaa ei löytynyt.\n" );
        exit( 1 );
    }

    return 0;
}


int isInLine( char *p, char *r )
{
    /* Mikäli 8 ensimmäistä kirjainta vastaavat toisiaan,
     * palautetaan 1 eli true, muussa tapauksessa 0 eli false.
     */
    int i = 0;
    for( i = 0; i < 8; i++)
    {
        if( p[i] != r[i] )
            return 0;
    }
    return 1;
}

