id = 0
x = 0
y = 0
function init()
   init_renderer()
   create_window("Example Project", 256, 256)
   id = load_bmp("default.bmp", 1)
   reshape_texture(id, x, y, 54, 54)
end

function main()
   while true do
      if (is_key_held("Escape")) then
	 break
      end	 
      
      if (is_key_held("Right")) then
	 x = x + 1
	 reshape_texture(id, x, y, 54, 54)
      end

      if (is_key_held("Left")) then
	 x = x - 1
	 reshape_texture(id, x, y, 54, 54)
      end

      draw_texture(id)
      
      redraw_window()
   end
end
