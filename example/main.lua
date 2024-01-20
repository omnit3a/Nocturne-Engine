function init()
   init_renderer()
   create_window("Example Project", 256, 256)
   id = load_bmp("default.bmp", 1)
   x = 0
   y = 0
   reshape_texture(id, x, y, 54, 54)
end

function close()
   destroy_window()
   os.exit()
end

function update()
   if is_key_held("Escape") then
      close_game()
   end
   
   if is_key_held("Right") then
      x = x + 4
      reshape_texture(id, x, y, 54, 54);
   end

   if is_key_held("Left") then
      x = x - 4
      reshape_texture(id, x, y, 54, 54);
   end

   draw_texture(id);   
   redraw_window()
end
