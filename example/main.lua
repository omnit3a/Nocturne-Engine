function init()
   init_renderer()
   create_window("Game!", 256, 256)
end

function main()
   while true do
      escape = is_key_held("Escape")
      shift = is_key_held("Left Shift")
      if (escape and shift) then
	 break
      end
      redraw_window()
   end
end
