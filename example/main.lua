id = 0
function init()
   init_renderer()
   create_window("Example Project", 256, 256)
   id = load_bmp("default.bmp", 1)
   reshape_texture(id, 0, 0, 54, 54)
end

function main()
   while true do
      if (is_key_held("Escape")) then
	 break
      end	 
      
      draw_texture(id)
      
      redraw_window()
   end
end
