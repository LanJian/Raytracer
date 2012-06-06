jade = gr.material({0.54, 0.89, 0.63}, {0.316228, 0.316228, 0.316228}, 12.8, 0.15)
red = gr.material({0.89, 0.3, 0.3}, {0.316228, 0.316228, 0.316228}, 12.8, 0)
boatMat = gr.material({0.8, 0.5, 0.6}, {0.316228, 0.316228, 0.316228}, 12.8, 0.1)
lake = gr.material({0.51, 0.62, 0.59}, {0.316228, 0.316228, 0.316228}, 12.8, 0.8)
black = gr.material({0.08, 0.08, 0.08}, {0, 0, 0}, 0, 0)

scene = gr.node('scene')

-- sword
sword = gr.node('sword')

s1 = gr.cube('s1')
sword:add_child(s1)
s1:set_material(jade)
s1:scale(3, 8, 1)

s4 = gr.cube('s4')
sword:add_child(s4)
s4:set_material(jade)
s4:translate(-0.3, 2, -0.3)
s4:scale(3.6, 1, 1.6)

s5 = gr.cube('s5')
sword:add_child(s5)
s5:set_material(jade)
s5:translate(-0.3, 4, -0.3)
s5:scale(3.6, 1, 1.6)

s6 = gr.cube('s6')
sword:add_child(s6)
s6:set_material(jade)
s6:translate(-0.3, 6, -0.3)
s6:scale(3.6, 1, 1.6)

s2 = gr.cube('s2')
sword:add_child(s2)
s2:set_material(jade)
s2:translate(-4, -1, -1)
s2:scale(11, 1, 3)

s3 = gr.mesh('pyramid', {
		   { 0.5, 0, 0 }, 
		   { 0, 0, -0.5}, 
		   { 0.5, 0, -1 }, 
		   { 1, 0, -0.5  },
		   { 0.5, 1, 0 }, 
		   { 0, 1, -0.5}, 
		   { 0.5, 1, -1 }, 
		   { 1, 1, -0.5  }
		}, {
		   {0, 1, 2, 3},
		   {0, 4, 5, 1},
		   {1, 5, 6, 2},
		   {2, 6, 7, 3},
		   {3, 7, 4, 0},
		   {7, 6, 5 ,4}
		})
sword:add_child(s3)
s3:set_material(jade)
s3:translate(-1.5, -41, 1)
s3:scale(6, 40, 1)


-- deco
deco = gr.node('deco')
d = gr.sphere('d')
deco:add_child(d)
d:set_material(red)
d:scale(0.1,2,0.1)
d:translate(0, 1, 0)
for i=0,2 do
  d1 = gr.sphere('d1')
  deco:add_child(d1)
  d1:set_material(red)
  d1:translate(0,-2*i, 0)
end

-- pyramid
pyramid = gr.mesh('pyramid', {
		   { -0.5, 0, -0.5 }, 
		   { 0.5, 0, -0.5}, 
		   { 0.5, 0, 0.5 }, 
		   { -0.5, 0, 0.5  },
		   { -0.05, 1, -0.05 },
		   { 0.05, 1, -0.05 },
		   { 0.05, 1, 0.05 },
		   { -0.05, 1, 0.05 }
		}, {
		   {0, 1, 2, 3},
		   {0, 4, 5, 1},
		   {1, 5, 6, 2},
		   {2, 6, 7, 3},
		   {3, 7, 4, 0},
		   {7, 6, 5 ,4}
		})

b1 = gr.node('b1')
b1:add_child(pyramid)
pyramid:set_material(jade)
b1:translate(-7,0,-5)
b1:scale(8, 8, 8)
b1:rotate('Y', -30)
b1:rotate('X', -30)

-- base
base = gr.node('base')
a = 0
for i=0,2 do
  for j=0,7 do
    spike = gr.node('spike' .. tostring(a))
    base:add_child(spike)
    spike:add_child(pyramid)
    pyramid:set_material(jade)
    spike:translate(0, 0.5*i, 0)
    spike:rotate('Y', i*15+j*45)
    spike:rotate('Z', -70+i*10)
    spike:translate(0, 3+i, 0)
    spike:scale(1,12-i*3.5,6-i*2)
  end
end

-- lake
plane = gr.mesh('plane', {
		   { -1, 0, -1 }, 
		   {  1, 0, -1 }, 
		   {  1,  0, 1 }, 
		   { -1, 0, 1  }
		}, {
		   {3, 2, 1, 0}
		})

-- boat
boat = gr.node('boat')
bbase = gr.mesh('pyramid', {
		   { 0, 0, 0 }, 
		   { 1, 0, 0}, 
		   { 1, 0, 1 }, 
		   { 0, 0, 1  },
		   { 0, -1, 0.5 },
		   { 1, -1, 0.5 }
		}, {
		   {3, 2, 1, 0},
		   {0, 4, 3},
		   {1, 2, 5},
		   {0, 1, 5, 4},
		   {2, 3, 4, 5},
		})
boat:add_child(bbase)
bbase:set_material(boatMat)
bbase:scale(3, 1, 1)

cabin = gr.cube('cabin')
boat:add_child(cabin)
cabin:set_material(red)
cabin:scale(1,0.6,0.6)
cabin:translate(0.4,0,0.2)

-- add stuff to scene
scene:add_child(plane)
plane:set_material(lake)
plane:translate(0,-5,0)
plane:scale(50, 50, 50)

sword_inst1 = gr.node('si1')
sword_inst1:add_child(sword)
sword_inst1:translate(-12,15,0)
sword_inst1:rotate('Z', 15)
sword_inst1:rotate('Y', 30)

base_inst1 = gr.node('bi1')
base_inst1:add_child(base)
base_inst1:translate(-5, -6, 0)

deco_inst = gr.node('di')
deco_inst:add_child(deco)
deco_inst:translate(-14, 18, 0)
deco_inst:scale(0.7,0.7,0.7)

inst1 = gr.node('i1')
inst1:add_child(sword_inst1)
inst1:add_child(deco_inst)
inst1:add_child(base_inst1)
inst1:translate(-11,-3,3)
inst1:scale(0.6,0.6,0.6)

inst2 = gr.node('i2')
inst2:add_child(sword_inst1)
inst2:add_child(base_inst1)
inst2:translate(6.5,-3,14)
inst2:rotate('Y', 160)
inst2:scale(0.6,0.6,0.6)

inst3 = gr.node('i3')
inst3:add_child(sword_inst1)
inst3:add_child(base_inst1)
inst3:translate(-2,-3,-18)
inst3:rotate('Y', 90)
inst3:scale(0.6,0.6,0.6)

inst4 = gr.node('i4')
inst4:add_child(sword_inst1)
inst4:add_child(deco_inst)
inst4:add_child(base_inst1)
inst4:translate(17,-3,-18)
inst4:rotate('Y', 180)
inst4:scale(0.5,0.5,0.5)

inst5 = gr.node('i5')
inst5:add_child(sword_inst1)
inst5:add_child(base_inst1)
inst5:translate(-20,-3,-32)
inst5:rotate('Y', 130)
inst5:scale(0.5,0.5,0.5)

inst6 = gr.node('i6')
inst6:add_child(sword_inst1)
inst6:add_child(deco_inst)
inst6:add_child(base_inst1)
inst6:translate(-40,-3,-20)
inst6:rotate('Y', 30)
inst6:scale(0.6,0.6,0.6)

inst7 = gr.node('i7')
inst7:add_child(sword_inst1)
inst7:add_child(base_inst1)
inst7:translate(8,-3,-40)
inst7:rotate('Y', -10)
inst7:scale(0.5,0.5,0.5)

-- mountain
mountain = gr.node('mountain')

m1 = gr.sphere('m1')
m1:set_material(black)
m1:scale(15, 40, 1)
m2 = gr.sphere('m2')
m2:set_material(black)
m2:translate(25,0,2)
m2:scale(10, 27, 1)
m3 = gr.sphere('m3')
m3:set_material(black)
m3:translate(-25,0,2)
m3:scale(12, 47, 1)
m4 = gr.sphere('m4')
m4:set_material(black)
m4:translate(40,0,4)
m4:scale(8, 15, 1)
m5 = gr.sphere('m5')
m5:set_material(black)
m5:translate(-50,0,6)
m5:scale(7, 20, 1)

mountain:add_child(m1)
mountain:add_child(m2)
mountain:add_child(m3)
mountain:add_child(m4)
mountain:add_child(m5)
mountain:translate(0,-5,-45)


boat:translate(-4,-4.5,12)
boat:rotate('Y', 40)

scene:add_child(boat)

scene:add_child(inst1)
scene:add_child(inst2)
scene:add_child(inst3)
scene:add_child(inst4)
scene:add_child(inst5)
scene:add_child(inst6)
scene:add_child(inst7)

scene:add_child(mountain)

white_light = gr.light({10,10,7}, {0.7, 0.7, 0.6}, {1, 0, 0})
gr.render(scene, 'sample.png', 1000, 500, 
	  {0, 0, 30,}, {0, 0, -1}, {0, 1, 0}, 55,
	  {0.3, 0.3, 0.3}, {white_light}, 80)
