So far:

for a non-specific texture to be rendered and loaded and have an input:

  createSprite()
    initialize the struct with everything we may need!
  placeSprite()
    choose when and where the Sprite dest rect is placed!!!
  updateSprite()
    SDL_RenderClear() // beginning of function
    // choose what input modifies the Sprite!!!!
    SDL_RenderCopy() // end of function
  renderSprite()
    SDL_Present // Show visible changes!!!
  destroySprite()
    SDL_DestroyTexture // Get rid of our Sprite before closing!

  For input, the difference:
  Mouse:
  SDL_GetMouseState()
  Keyboard:
  Uint8* pkeys = SDL_GetKeyboardState()

  Both use event.type!!
