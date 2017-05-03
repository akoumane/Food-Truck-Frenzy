#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif



void printBrandonName();
void TitleScreen();
void renderTitleScreen();
void Level_Menu();
void renderLevelScreen();
void Pause_Menu();
void renderPauseScreen();
void input_title_screen();
void Option_Menu();
void Help_Menu();
void renderHelpScreen();
void Defeat_Menu();
void renderDefeatScreen();
void LeaderBoard_Menu();
void checkKeys(XEvent *e);
#ifdef USE_OPENAL_SOUND
void initSound();
void cleanupSound();
void playSound(ALuint source);
#endif
