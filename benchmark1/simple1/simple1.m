figure(1)
axis equal;
hold on
grid on
% area range
block_x=[ 0 0 18 18 0];
block_y=[ 0 20 20 0 0];
fill(block_x,block_y,'w','Edgecolor','r');
% block location
block_x=[ 0 0 8 8 0 ];
block_y=[ 0 8 8 0 0 ];
fill(block_x,block_y,'c');
text(4,4,'o0');
block_x=[ 8 8 14 14 8 ];
block_y=[ 0 4 4 0 0 ];
fill(block_x,block_y,'c');
text(11,2,'o1');
block_x=[ 14 14 18 18 14 ];
block_y=[ 0 10 10 0 0 ];
fill(block_x,block_y,'c');
text(16,5,'o2');
block_x=[ 0 0 10 10 0 ];
block_y=[ 8 14 14 8 8 ];
fill(block_x,block_y,'c');
text(5,11,'o3');
block_x=[ 10 10 16 16 10 ];
block_y=[ 10 16 16 10 10 ];
fill(block_x,block_y,'c');
text(13,13,'o4');
block_x=[ 0 0 6 6 0 ];
block_y=[ 14 20 20 14 14 ];
fill(block_x,block_y,'c');
text(3,17,'o5');
grid
figure(2)
axis equal;
hold on
grid on
% area range
line([0 0],[0 20],'color','g')
line([0 6],[20 20],'color','g')
line([6 6],[20 14],'color','g')
line([6 10],[14 14],'color','g')
line([10 10],[14 16],'color','g')
line([10 16],[16 16],'color','g')
line([16 16],[16 10],'color','g')
line([16 18],[10 10],'color','g')
line([18 18],[10 0],'color','g')
grid
