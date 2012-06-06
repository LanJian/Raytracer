mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25, 0.6)
mat2 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0.6)


scene_root = gr.node('root')

sphere = gr.sphere('sphere')
sphere:set_material(mat1)

cube = gr.cube('cube')
cube:set_material(mat2)

i = 0;
for a = -1, 1, 2 do
  for b = -1, 1, 2 do
    for c = 0, 4 do
      sphere_instance = gr.node('sphere' .. tostring(i))
      scene_root:add_child(sphere_instance)
      sphere_instance:add_child(sphere)
      sphere_instance:scale(100,100,100)
      sphere_instance:translate(a*4, b*4, -(c*5+5))

      i = i+1
    end
  end
end

i = 0;
for a = -1, 1, 2 do
  for c = 0, 4 do
    cube_instance = gr.node('cube' .. tostring(i))
    scene_root:add_child(cube_instance)
    cube_instance:add_child(cube)
    cube_instance:scale(100,100,100)
    cube_instance:translate(-0.5, -0.5, -0.5)
    cube_instance:translate(a*4, 0, -(c*5+5))

    i = i+1
  end
end

i = 0;
for a = -1, 1, 2 do
  for c = 0, 4 do
    cube_instance = gr.node('cube' .. tostring(i))
    scene_root:add_child(cube_instance)
    cube_instance:add_child(cube)
    cube_instance:scale(100,100,100)
    cube_instance:translate(-0.5, -0.5, -0.5)
    cube_instance:translate(0, a*4, -(c*5+5))

    i = i+1
  end
end


white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, 'fog.png', 600, 600,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light}, 3000)
