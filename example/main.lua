function init()
   init_renderer()
   create_window("Game!", 640, 480)
end

function main()
   while true do
      if is_key_down("Q") then
	 break
      end
      redraw_window()
   end
end
