figure(1)
axis equal;
hold on
grid on
% area range
block_x=[ 0 0 78 78 0];
block_y=[ 0 100 100 0 0];
fill(block_x,block_y,'w','Edgecolor','r');
% block location
block_x=[ 0 0 20 20 0 ];
block_y=[ 0 30 30 0 0 ];
fill(block_x,block_y,'c');
text(10,15,'m1');
block_x=[ 20 20 44 44 20 ];
block_y=[ 0 24 24 0 0 ];
fill(block_x,block_y,'c');
text(32,12,'m2');
block_x=[ 44 44 66 66 44 ];
block_y=[ 0 32 32 0 0 ];
fill(block_x,block_y,'c');
text(55,16,'m3');
block_x=[ 66 66 76 76 66 ];
block_y=[ 0 10 10 0 0 ];
fill(block_x,block_y,'c');
text(71,5,'m4');
block_x=[ 66 66 74 74 66 ];
block_y=[ 10 20 20 10 10 ];
fill(block_x,block_y,'c');
text(70,15,'m5');
block_x=[ 44 44 78 78 44 ];
block_y=[ 32 54 54 32 32 ];
fill(block_x,block_y,'c');
text(61,43,'m6');
block_x=[ 20 20 44 44 20 ];
block_y=[ 24 50 50 24 24 ];
fill(block_x,block_y,'c');
text(32,37,'m7');
block_x=[ 44 44 64 64 44 ];
block_y=[ 54 70 70 54 54 ];
fill(block_x,block_y,'c');
text(54,62,'m8');
block_x=[ 20 20 42 42 20 ];
block_y=[ 50 66 66 50 50 ];
fill(block_x,block_y,'c');
text(31,58,'m9');
block_x=[ 0 0 20 20 0 ];
block_y=[ 30 70 70 30 30 ];
fill(block_x,block_y,'c');
text(10,50,'m10');
block_x=[ 20 20 32 32 20 ];
block_y=[ 66 78 78 66 66 ];
fill(block_x,block_y,'c');
text(26,72,'m11');
block_x=[ 32 32 48 48 32 ];
block_y=[ 70 80 80 70 70 ];
fill(block_x,block_y,'c');
text(40,75,'m12');
block_x=[ 20 20 32 32 20 ];
block_y=[ 78 88 88 78 78 ];
fill(block_x,block_y,'c');
text(26,83,'m13');
block_x=[ 0 0 16 16 0 ];
block_y=[ 70 84 84 70 70 ];
fill(block_x,block_y,'c');
text(8,77,'m14');
block_x=[ 16 16 20 20 16 ];
block_y=[ 70 90 90 70 70 ];
fill(block_x,block_y,'c');
text(18,80,'m15');
block_x=[ 0 0 30 30 0 ];
block_y=[ 90 100 100 90 90 ];
fill(block_x,block_y,'c');
text(15,95,'m16');
grid
figure(2)
axis equal;
hold on
grid on
% area range
line([0 0],[0 100],'color','g')
line([0 30],[100 100],'color','g')
line([30 30],[100 88],'color','g')
line([30 32],[88 88],'color','g')
line([32 32],[88 80],'color','g')
line([32 48],[80 80],'color','g')
line([48 48],[80 70],'color','g')
line([48 64],[70 70],'color','g')
line([64 64],[70 54],'color','g')
line([64 78],[54 54],'color','g')
line([78 78],[54 0],'color','g')
grid
