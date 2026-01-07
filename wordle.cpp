#include "wordlefunc.h"
#include "raylib.h"
#include <vector>
#include <string>
#include <algorithm>


int main() {
    std::srand(std::time(0));
    InitWindow(450, 600, "Joels Wordle");
    SetTargetFPS(60);

    WordleData speletsData = ladda_all_data();
    std::string rattOrd = slumpa_ord(speletsData);
    std::transform(rattOrd.begin(), rattOrd.end(), rattOrd.begin(), ::toupper);

    std::string nuvarandeInput = "";
    int försök = 0;
    std::vector<SparadGissning> historik;
    int screen = 0;

    while (!WindowShouldClose()){
        if (screen == 0){
            if (IsKeyPressed(KEY_ONE)) screen = 1;
        }
        else if (screen == 1){

            int key = GetCharPressed(); 
            
            if (key >= 32 && key <= 125 && nuvarandeInput.length() < 5){
                nuvarandeInput += (char)toupper(key);
            }
            if (IsKeyPressed(KEY_BACKSPACE) && nuvarandeInput.length() > 0){
                nuvarandeInput.pop_back();
            }
            if (IsKeyPressed(KEY_ENTER) && nuvarandeInput.length() == 5){
                if (ar_gissning_giltig(nuvarandeInput, speletsData)){
                    std::vector<Resultat> r = kolla_gissning(nuvarandeInput, rattOrd);
                    historik.push_back({nuvarandeInput, r});
                    nuvarandeInput = "";
                    försök++; 
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (screen == 0){
            DrawText("JOELS WORDLE", 100, 200, 30, BLACK);
            DrawText("Tryck (1) för att starta", 100, 300, 20, GRAY); 
        }
        else {
            for (int rad = 0; rad < 6; rad++){
                for (int kol = 0; kol < 5; kol++){
                    int x = 50 + kol * 70;
                    int y = 50 + rad * 70; 

                    Color ruteFärg = RAYWHITE;
                    Color textFärg = BLACK;

                    if (rad < (int)historik.size()){
                        Resultat res = historik[rad].färger[kol];
                        if (res == GRON) ruteFärg = GREEN;
                        else if (res == GUL) ruteFärg = GOLD;
                        else if (res == GRA) ruteFärg = GRAY;
                        textFärg = WHITE;

                        DrawRectangle(x, y, 60, 60, ruteFärg);
                    }

                    DrawRectangleLines(x, y, 60, 60, LIGHTGRAY);

                    if (rad < historik.size()){
                        char b[2] = { historik[rad].ord[kol], '\0' };
                        DrawText(b, x + 20, y + 15, 30, textFärg);
                    }

                    else if (rad == försök && kol < nuvarandeInput.length()){
                        char bokstav[2] = { nuvarandeInput[kol], '\0' };
                        DrawText(bokstav, x + 20, y + 15, 30, BLACK);
                    }
                }
            }
            bool harVunnit = (!historik.empty() && historik.back().ord == rattOrd);
            bool harFörlorat = (försök >= 6 && !harVunnit);

            if (harVunnit){
                DrawRectangle(0, 0, 450, 600, Fade(WHITE, 0.8f));
                DrawText("GRATTIS! Du vann!", 100, 250, 25, GREEN);
                DrawText("Tryck (M) för menyn", 125, 300, 15, DARKGRAY);
            }
            else if (harFörlorat){
                DrawRectangle(0, 0, 450, 600, Fade(WHITE, 0.8f));
                DrawText("GAME OVER", 150, 250, 25, RED);
                std::string facitText = "Rätt ord var: " + rattOrd;
                DrawText(facitText.c_str(), 110, 300, 20, DARKGRAY);
                DrawText("Tryck (M) för menyn", 125, 350, 15, GRAY);
            }
            if ((harVunnit || harFörlorat) && IsKeyPressed(KEY_M)) {
                historik.clear();
                försök = 0;
                nuvarandeInput = "";
                rattOrd = slumpa_ord(speletsData);
                std::transform(rattOrd.begin(), rattOrd.end(), rattOrd.begin(), ::toupper);
                screen = 0;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}