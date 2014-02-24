    function footerImage(canvasID, size, color){
            var canvas = document.getElementById(canvasID),
                context = canvas.getContext('2d'),
                //how many isotopes are there of each element
                isotopesPerRow = [1,6,8,8,9,13,15,15,15,16,18,19,19,20,21,23,24,24,22,23,21,20,21,25,25,26,28,28,30,29,30,31,32,33,30,30,32,31],  //Rb last
                //offset of proton drip line from hydrogen 
                protonDrip = [1,0,1,1,2,2,2,3,4,5,5,6,7,8,8,9,10,11,12,13,14,15,16,17,18,19,19,21,21,23,24,25,26,27,31,33,33,35],
                //indices of stable isotopes relative to that element's proton drip
                stable = [
                    [], [0,1], [0,1], [2,3], [3], [3,4], [4,5], [4,5], [4,5,6], [5], [5,6,7],
                    [6], [5,6,7], [6], [6,7,8], [7], [6,7,8,10], [7,9], [6,8,10], [7,9], [6,8,9,10,12],
                    [9], [8,9,10,11,12], [11], [10,11,12], [11], [9, 11,12,13], [11], [9, 11,12,13,15], [11,13], [10,12,13,14],
                    [13,15], [12,14,15,16,18], [15], [9,11,12,13,15], [11,13], [11,13,14,15,17], [13]
                ],
                cell = 4*size,
                y0 = $('#'+canvasID).height() - cell/2,
                i,j;

            for(i=0; i<isotopesPerRow.length; i++){
                for(j=0; j<isotopesPerRow[i]; j++){
                    if( stable[i].indexOf(j) != -1 ){
                        context.strokeStyle = '#FF3399';
                        context.fillStyle = '#FF3399';
                    } else{
                       context.strokeStyle = color;
                       context.fillStyle = color;
                    }
                    context.beginPath();
                    context.arc(cell*protonDrip[i] + cell/2 + j*cell, y0, size, 0, 2*Math.PI);
                    context.closePath();
                    context.fill();
                    context.stroke();
                }
                y0 -= cell;
                if(y0<0) return;
            }

        }
