/* use info from
 * https://www.carnetdumaker.net/articles/faire-une-barre-de-progression-avec-arduino-et-liquidcrystal/
 * https://www.carnetdumaker.net/snippets/1/
 * sketck adapted by Nicu FLORICA (niq_ro) from http://www.tehnic.go.ro
*/

/* Inclut la bibliothéque LiquidCrystal pour l'écran LCD */
#include <LiquidCrystal.h>

/* Créer l'objet lcd avec une configuration de broches compatible avec shield LCD de DFRobots */
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


/* Constantes pour la taille de l'écran LCD */
const int LCD_NB_ROWS = 2;
const int LCD_NB_COLUMNS = 16;


/* Caractères personnalisés */
byte DIV_0_OF_5[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
}; // 0 / 5

byte DIV_1_OF_5[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
}; // 1 / 5

byte DIV_2_OF_5[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
}; // 2 / 5

byte DIV_3_OF_5[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
}; // 3 / 5

byte DIV_4_OF_5[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
}; // 4 / 5

byte DIV_5_OF_5[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
}; // 5 / 5


/**
 * Fonction de configuration de l'écran LCD pour la barre de progression.
 * Utilise les caractéres personnalisés de 0 à 5 (6 et 7 restent disponibles).
 */
void setup_progressbar() {

  /* Enregistre les caractères personnalisés dans la mémoire de l'écran LCD */
  lcd.createChar(0, DIV_0_OF_5);
  lcd.createChar(1, DIV_1_OF_5);
  lcd.createChar(2, DIV_2_OF_5);
  lcd.createChar(3, DIV_3_OF_5);
  lcd.createChar(4, DIV_4_OF_5);
  lcd.createChar(5, DIV_5_OF_5);
}


/**
 * Fonction dessinant la barre de progression.
 *
 * @param percent Le pourcentage à afficher.
 */
void draw_progressbar(byte percent) {

  /* Affiche la nouvelle valeur sous forme numérique sur la premiére ligne */
  lcd.setCursor(0, 0);
  if (percent < 100)  lcd.print(" ");
  if (percent < 10)  lcd.print(" ");
  lcd.print(percent);
  lcd.print(F(" %  "));
  // N.B. Les deux espaces en fin de ligne permettent d'effacer les chiffres du pourcentage
  // précédent quand on passe d'une valeur à deux ou trois chiffres à une valeur à deux ou un chiffre.

  /* Déplace le curseur sur la seconde ligne */
  lcd.setCursor(0, 1);

  /* Map la plage (0 ~ 100) vers la plage (0 ~ LCD_NB_COLUMNS * 5) */
  byte nb_columns = map(percent, 0, 100, 0, LCD_NB_COLUMNS * 5);

  /* Dessine chaque caractére de la ligne */
  for (byte i = 0; i < LCD_NB_COLUMNS; ++i) {

    /* En fonction du nombre de colonnes restant à afficher */
    if (nb_columns == 0) { // Case vide
      lcd.write((byte) 0);

    } else if (nb_columns >= 5) { // Case pleine
      lcd.write(5);
      nb_columns -= 5;

    } else { // Derniére case non vide
      lcd.write(nb_columns);
      nb_columns = 0;
    }
  }
}


/** Fonction setup() */
void setup(){

  /* Initialise l'écran LCD */
  lcd.begin(LCD_NB_COLUMNS, LCD_NB_ROWS);
  setup_progressbar();
  lcd.clear();
  delay(2000);
}


/** Fonction loop() */
void loop(){

  /* Valeur en pourcent de la barre de progression */
  static byte percent = 0;

  /* Affiche la valeur */
  draw_progressbar(percent);

  /* Incrémente le pourcentage */
  if (++percent == 101) {
    // Revient à zéro si le pourcentage dépasse 100%
    percent = 0;
    delay(1000);
  }

  /* Petit temps d'attente */
  delay(250);
}
