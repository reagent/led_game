# Arudino LED Game

![Arduino LED Game](https://raw.github.com/reagent/led_game/master/game.jpg)

This is a simple Arduino-based game that requires the player to match the color of a tri-color LED to random colors selected by the computer player.  The play sequence is:

1. Player presses the button to start the game
2. Computer displays the random RGB colors one at a time and plays a ready tone
3. Computer then lights the three random colors simultaneously and plays a 'go' tone
4. Player selects the intensity of the red, green, and blue values using the 3 dials
5. Player presses the button to submit their choices
6. Game emits either a 'success' or 'error' tone indicating whether the choices were correct

In order to make it even remotely possible to match the colors, there are only 3 options for each color - off, low, and high.

Enjoy!