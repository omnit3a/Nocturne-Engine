function init()
   init_renderer()
   create_window("Example Project", 256, 256)
   id = load_bmp("default.bmp", 1)
   x = 0
   y = 0
   reshape_texture(id, x, y, 54, 54)
end

function main()
   while true do
      if (is_key_held("Escape")) then
	 break
      end
      
      if (is_key_held("Right")) then
	 x = x + 1
	 reshape_texture(id, x, y, 54, 54);
      end

      if (is_key_held("Left")) then
	 x = x - 1
	 reshape_texture(id, x, y, 54, 54);
      end

      draw_offset_texture(id, 0, 0, 16, 16);
      
      redraw_window()
   end
end
