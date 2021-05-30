figure(1)
axis equal;
hold on
grid on
% area range
block_x=[ 0 0 6885 6885 0];
block_y=[ 0 6951 6951 0 0];
fill(block_x,block_y,'w','Edgecolor','r');
% block location
block_x=[ 0 0 1731 1731 0 ];
block_y=[ 0 3318 3318 0 0 ];
fill(block_x,block_y,'c');
text(865,1659,'cc_12');
block_x=[ 1731 1731 5882 5882 1731 ];
block_y=[ 0 1383 1383 0 0 ];
fill(block_x,block_y,'c');
text(3806,691,'cc_13');
block_x=[ 5882 5882 6162 6162 5882 ];
block_y=[ 0 843 843 0 0 ];
fill(block_x,block_y,'c');
text(6022,421,'clk');
block_x=[ 1731 1731 3760 3760 1731 ];
block_y=[ 1383 4259 4259 1383 1383 ];
fill(block_x,block_y,'c');
text(2745,2821,'cc_21');
block_x=[ 3760 3760 6883 6883 3760 ];
block_y=[ 1383 3222 3222 1383 1383 ];
fill(block_x,block_y,'c');
text(5321,2302,'cc_14');
block_x=[ 3760 3760 6883 6883 3760 ];
block_y=[ 3222 5090 5090 3222 3222 ];
fill(block_x,block_y,'c');
text(5321,4156,'cc_22');
block_x=[ 0 0 1582 1582 0 ];
block_y=[ 3318 6949 6949 3318 3318 ];
fill(block_x,block_y,'c');
text(791,5133,'cc_11');
block_x=[ 1582 1582 3750 3750 1582 ];
block_y=[ 4259 6951 6951 4259 4259 ];
fill(block_x,block_y,'c');
text(2666,5605,'cc_23');
block_x=[ 3750 3750 6885 6885 3750 ];
block_y=[ 5090 6951 6951 5090 5090 ];
fill(block_x,block_y,'c');
text(5317,6020,'cc_24');
grid
figure(2)
axis equal;
hold on
grid on
% area range
line([0 0],[0 6949],'color','g')
line([0 1582],[6949 6949],'color','g')
line([1582 1582],[6949 6951],'color','g')
line([1582 3750],[6951 6951],'color','g')
line([3750 3750],[6951 6951],'color','g')
line([3750 6885],[6951 6951],'color','g')
line([6885 6885],[6951 0],'color','g')
grid
