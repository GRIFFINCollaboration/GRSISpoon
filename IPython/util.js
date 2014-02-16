define(function(){
    //////////////////////////////////
    //demo functions    
    //////////////////////////////////
    var selected = function(selectID){
            var select = document.getElementById(selectID),
                value = select.options[select.selectedIndex].value;

            return value;
        }

    var drawImg = function(imgId, out_type, out){
            document.getElementById(imgId).src = 'data:image/png;base64,' + out.data['image/png'];       
        }

    var exec_code = function(){
            var kernel = IPython.notebook.kernel;
            var callbacks = {'output' : drawImg.bind(null, 'imgtarget')};
            kernel.execute('testVar = "' + selected('plotOptions') + '"');
            kernel.execute('ROOTplot(testVar)', callbacks, {silent:false});
        }

    var registerLeafList = function(out_type, out){
            var rawString = out.data['text/plain'],
                kernel = IPython.notebook.kernel,
                options, i, opt;
            
            //lose the leading and trailing ' and the trailing &
            rawString = rawString.slice(1, rawString.length-2)
        
            options = rawString.split('&');
            for(i=0; i<options.length; i++){
                opt = document.createElement('option');
                opt.innerHTML = options[i];
                opt.value = options[i];
                document.getElementById('plotOptions').appendChild(opt);
            }
        }
    
    var getListOfVariables = function(){
            console.log('getting variables...')
            var kernel = IPython.notebook.kernel;
            var callbacks = {'output' : registerLeafList};
            kernel.execute('listtree()', callbacks, {silent:false});
        }

    //////////////////////////////////////
    //branding
    //////////////////////////////////////
    var GRSISpoon = function(canvasID, size){
	    var canvas = document.getElementById(canvasID),
	    context = canvas.getContext('2d')

            context.strokeStyle = '#FFFFFF';
 
            context.shadowBlur = size/4;
            context.shadowColor = '#FFFFFF';
	    context.lineWidth = 2;
            context.moveTo(0, 1.3*size);
	    context.lineTo(3*size, 1.35*size);
            context.bezierCurveTo(6.5*size, -0.5*size, 6.5*size, 3.5*size, 3*size, 1.65*size)
	    context.lineTo(0, 1.7*size);
            context.stroke();
	
            context.fillStyle = '#FFFFFF';			
	    context.font = 0.8*size+'px Arial';
	    context.fillText('GRSISpoon', 0.2*size, 2.8*size)
	}

    var footerImage = function(canvasID, size){
            var canvas = document.getElementById(canvasID),
                context = canvas.getContext('2d'),
                isotopesPerRow = [1,6,8,8,9,13,15,15,15,16,18,19,19,20,21,23,24,24,22,23,21,20,21,25,25,26,28,28,30,29,30,31,32,33,30,30,32,31],  //Rb last 
                protonDrip = [1,0,1,1,2,2,2,3,4,5,5,6,7,8,8,9,10,11,12,13,14,15,16,17,18,19,19,21,21,23,24,25,26,27,31,33,33,35],
                stable = [
                    [], [0,1], [0,1], [2,3], [3], [3,4], [4,5], [4,5], [4,5,6], [5], [5,6,7],
                    [6], [5,6,7], [6], [6,7,8], [7], [6,7,8,10], [7,9], [6,8,10], [7,9], [6,8,9,10,12],
                    [9], [8,9,10,11,12], [11], [10,11,12], [11], [9, 11,12,13], [11], [9, 11,12,13,15], [11,13], [10,12,13,14],
                    [13,15], [12,14,15,16,18], [15], [9,11,12,13,15], [11,13], [11,13,14,15,17], [13]
                ],
                cell = 4*size,
                y0 = $('#footerImage').height() - cell/2,
                i,j;

            for(i=0; i<isotopesPerRow.length; i++){
                for(j=0; j<isotopesPerRow[i]; j++){
                    if( stable[i].indexOf(j) != -1 ){
                        context.strokeStyle = '#FF3399';
                        context.fillStyle = '#FF3399';
                    } else{
                       context.strokeStyle = '#333333';
                       context.fillStyle = '#333333';
                    }
                    context.beginPath();
                    context.arc(cell*protonDrip[i] + cell/2 + j*cell, y0, size, 0, 2*Math.PI);
                    context.closePath();
                    context.fill();
                    context.stroke();
                }
                y0 -= cell;
            }

        }


    //////////////////////////////////////
    //system load monitor
    //////////////////////////////////////

    var constructHexColor = function(color){
            var R = Math.round(color[0]);
            var G = Math.round(color[1]);
            var B = Math.round(color[2]);

            R = R.toString(16);
            G = G.toString(16);
            B = B.toString(16);

            if(R.length == 1) R = '0'+R;
            if(G.length == 1) G = '0'+G;
            if(B.length == 1) B = '0'+B;

            return '#'+R+G+B;
        }

        //map [0,1] onto various color scales
        var scalepickr = function(scale, palette){
            //map scale onto [0,360]:
            var H = scale*300 / 60;
            if(H>5) H=5;
            if(H<0) H=0;
            var R, G, B;
            var start0, start1, start2, start3, start4, start5;
            if (palette == 'Sunset'){
                start0 = [0,0,0];
                start1 = [0,0,0x52];
                start2 = [0xE6,0,0x5C];
                start3 = [255,255,0];        
                start4 = [255,0x66,0];
                start5 = [255,0,0];        
            } else if (palette == 'ROOT Rainbow'){
                start0 = [0xFF,0x00,0x00];
                start1 = [0xFF,0xFF,0x00];
                start2 = [0x00,0xFF,0x00];
                start3 = [0x00,0xFF,0xFF];
                start4 = [0x00,0x00,0xFF];
                start5 = [0x66,0x00,0xCC];
                H = -1*(H-5);
            } else if (palette == 'Greyscale'){
                start0 = [0x00,0x00,0x00];
                start1 = [0x22,0x22,0x22];
                start2 = [0x55,0x55,0x55];
                start3 = [0x88,0x88,0x88];        
                start4 = [0xBB,0xBB,0xBB];
                start5 = [0xFF,0xFF,0xFF];
            } else if (palette == 'Red Scale'){
                start0 = [0x00,0x00,0x00];
                start1 = [0x33,0x00,0x00];
                start2 = [0x66,0x00,0x00];
                start3 = [0x99,0x00,0x00];
                start4 = [0xCC,0x00,0x00];
                start5 = [0xFF,0x00,0x00];
            } else if (palette == 'Mayfair'){
                start0 = [0x1E,0x4B,0x0F];
                start1 = [0x0E,0xBE,0x57];
                start2 = [0xE4,0xAB,0x33];
                start3 = [0xEC,0x95,0xF7];
                start4 = [0x86,0x19,0x4A];
                start5 = [0xFF,0x10,0x10];
            } else if (palette == 'Test'){
                start0 = [0x5E,0x1F,0x14];
                start1 = [0x74,0x4D,0x3E];
                start2 = [0x9D,0x47,0x05];
                start3 = [0xDF,0x67,0x19];
                start4 = [0xFE,0x83,0x54];
                start5 = [0x251,0x15,0x29];
            }
            if(H>=0 && H<1){
                R = start0[0] + Math.round(H*(start1[0]-start0[0]));
                G = start0[1] + Math.round(H*(start1[1]-start0[1]));
                B = start0[2] + Math.round(H*(start1[2]-start0[2]));
            } else if(H>=1 && H<2){
                R = start1[0] + Math.round((H-1)*(start2[0]-start1[0]));
                G = start1[1] + Math.round((H-1)*(start2[1]-start1[1]));
                B = start1[2] + Math.round((H-1)*(start2[2]-start1[2]));
            } else if(H>=2 && H<3){
                R = start2[0] + Math.round((H-2)*(start3[0]-start2[0]));
                G = start2[1] + Math.round((H-2)*(start3[1]-start2[1]));
                B = start2[2] + Math.round((H-2)*(start3[2]-start2[2]));
            } else if(H>=3 && H<4){
                R = start3[0] + Math.round((H-3)*(start4[0]-start3[0]));
                G = start3[1] + Math.round((H-3)*(start4[1]-start3[1]));
                B = start3[2] + Math.round((H-3)*(start4[2]-start3[2]));
            } else if(H>=4 && H<=5){
                R = start4[0] + Math.round((H-4)*(start5[0]-start4[0]));
                G = start4[1] + Math.round((H-4)*(start5[1]-start4[1]));
                B = start4[2] + Math.round((H-4)*(start5[2]-start4[2]));  
            }

            return constructHexColor([R,G,B]);
        }

    var illustrateMpstat = function(type, mpstat){
            var rawString = mpstat.data.split('\n'), 
                usage = [],                                               //array which will contain the usage in [0,1] of CPU i at index i.
		canvas = document.getElementById('systemUseCanvas'),
		context = canvas.getContext('2d'),
		barWidth = 20,                                                //width of bars, in px
		barHeight = 5,                                                //height of bar in px; 20 of these to a meter
		barSpace = 2,                                                 //space between bars, px
		meterSpace = 5,                                               //gutter between meters, px
		bottomGutter = 20,                                            //height of bottom gutter, px
                leftGutter = 100,                                             //width of left gutter, px
                topGutter = 20,                                               //height of top gutter, px
		canvasWidth,
		canvasHeight = barHeight*20 + barSpace*19 + bottomGutter + topGutter, //canvas height, px 
		i, j, nbins, x0, y0, label;


            //first four lines are header garbage
            for(i=4; i<rawString.length-1; i++){ //there's an extra newline at the end resulting in a garbage entry
                usage[i-4] = rawString[i].split(/[ ]+/);  //split on any amount of whitespace
                usage[i-4] = parseFloat(usage[i-4][3]) / 100.0;
            }
//console.log(usage)
for(i=0; i<32; i++){
 usage[i] = Math.random();
}

	    canvasWidth = leftGutter + usage.length*barWidth + (usage.length-1)*meterSpace; //canvas width, px

	    //scale canvas if necessary:
	    if( document.getElementById('systemUseCanvas').width != canvasWidth || document.getElementById('systemUseCanvas').height != canvasHeight){
                document.getElementById('systemUseCanvas').width = canvasWidth;
                document.getElementById('systemUseCanvas').height = canvasHeight;
	    }

	    //clear canvas:
	    context.clearRect(0,0,canvasWidth,canvasHeight);

            //draw frame:
            context.strokeStyle = '#444444';
            context.lineWidth = 1;
            context.font = '12px Arial';
            context.fillStyle = '#111111';
            for(i=0; i<5; i++){
                y0 = Math.round(canvasHeight - bottomGutter - i*(5*barHeight + 5*barSpace) + barSpace);
                context.moveTo(leftGutter, y0);
                context.lineTo(canvasWidth, y0);
                context.stroke();
                label = i*25 + '%';
                context.fillText(label, leftGutter - context.measureText(label).width - 2, y0 + 6);
            }

	    //draw a meter for each CPU
	    for(i=0; i<usage.length; i++){
                context.fillStyle = scalepickr(usage[i],'Red Scale');
	  	nbins = Math.ceil(usage[i] / 0.05); //how many rectangles to stack up?
		x0 = leftGutter + i*(barWidth + meterSpace); //left edge of this meter

		//draw each cell, one for every 5% or fraction thereof of usage on the ith CPU
		for(j=0; j<nbins; j++){
			context.fillRect(x0, canvasHeight - bottomGutter - barHeight*(j+1) - barSpace*j, barWidth, barHeight );
		}

                //x-labels
                context.fillStyle = '#111111';
                context.fillText(i, x0 + barWidth/2 - context.measureText(i).width/2, canvasHeight - bottomGutter + 16 );
	    }

        }

    var mpstatJS = function(){
            var kernel = IPython.notebook.kernel;
            var callbacks = {'output' : illustrateMpstat};
            kernel.execute('!mpstat -P ALL', callbacks, {silent:false});
        }

    //////////////////////////////////////
    //return object
    //////////////////////////////////////
    return {
        selected : selected,
        drawImg : drawImg,
        exec_code : exec_code,
        registerLeafList : registerLeafList,
        getListOfVariables : getListOfVariables,
        GRSISpoon : GRSISpoon,
        constructHexColor : constructHexColor,
        scalepickr : scalepickr,
        mpstatJS : mpstatJS,
        illustrateMpstat : illustrateMpstat,
        footerImage : footerImage
    }
});
