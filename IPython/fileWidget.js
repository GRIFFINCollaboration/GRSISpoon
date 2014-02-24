//toggle an element from one list to the other
function toggleElt(elt){
    var listID = (elt.parentNode.id == 'selectedFiles') ? 'unselectedFiles' : 'selectedFiles',
        fileList = document.getElementById(listID),
        i;
     
    for(i=0; i<fileList.children.length; i++){
        if(fileList.children[i].innerHTML == elt.innerHTML){
            elt.className = 'fileHidden';
            fileList.children[i].className = 'fileShowing';
            break;
        }
    }
        
    //don't need the hint anymore, hide it
    document.getElementById('fileWidgetHint').style.display = 'none';
        
    gradientList();        
}
    
    //double click insta-toggles:
    function fileDoubleClick(event){
            toggleElt(event.target);  
            return;                                    
    }

    //single click queues or unqueues for toggling:
    function fileClick(event){
        var fileElts, inRange;
        
        //just vanilla if no shift:
        if(!event.shiftKey){
            if(event.target.className.indexOf('fileSelected') == -1)
                event.target.className += ' fileSelected';
            else 
                event.target.className = event.target.className.slice(0, ' ');
        //shift highlights a range of elements
        } else{
            //if there's a boundary chosen, select everything between it and this element
            if(window.fileRangeBoundary){
                inRange = false;
                fileElts = document.querySelectorAll('ul#'+event.target.parentNode.id+' li');
                [].forEach.call(fileElts, function(elt){
                    //here we are at the start of the run of selected items:
                    if(!inRange && (elt == window.fileRangeBoundary || elt == event.target) ){
                        inRange = true;
                        if(elt.className.indexOf('fileSelected') == -1)
                            elt.className += ' fileSelected';
                    //at the end of the run:
                    } else if(inRange && (elt == window.fileRangeBoundary || elt == event.target)){
                        inRange = false;
                        if(elt.className.indexOf('fileSelected') == -1)
                            elt.className += ' fileSelected';
                    //in the middle of the run:
                    } else if(inRange){
                        if(elt.className.indexOf('fileSelected') == -1)
                            elt.className += ' fileSelected';                                       
                    }
                })
                window.fileRangeBoundary = null;
            //this must be the first of 2 boundaries, keep hold of it for later.
            } else {
                window.fileRangeBoundary = event.target;
                if(event.target.className.indexOf('fileSelected') == -1)
                    event.target.className += ' fileSelected';                
            }
        }
    }

//toggle all the selected files
function toggleQueuedFiles(){
    var fileElts = document.querySelectorAll('ul.fileList li');
    [].forEach.call(fileElts, function(elt){        
        if(elt.className.indexOf('fileSelected') != -1){
            //unhighlight:
            elt.className = elt.className.slice(0, ' ');
               
            //toggle:
            toggleElt(elt);
        }
    })        
}

    function gradientList(){
        var stepSize = 10,
            initUnselected = 175,
            lastUnselected = 255,
            unselectedSteps = (lastUnselected - initUnselected) / stepSize,
            initSelectedRed = 5,
            initSelectedGreen = 195,
            initSelectedBlue = 105,
            lastSelectedRed = 65,
            lastSelectedGreen = 255,
            lastSelectedBlue = 165,
            selectedSteps = (lastSelectedRed - initSelectedRed) / stepSize,
            unselectedFiles = document.querySelectorAll('ul#unselectedFiles li'),
            selectedFiles = document.querySelectorAll('ul#selectedFiles li'),
            index = 0,
            increment = 1;
            
        
        [].forEach.call(unselectedFiles, function(elt){
            if(elt.className != 'fileHidden'){
                elt.style.backgroundColor = 'rgba(' + (initUnselected + stepSize*index) + ', ' + (initUnselected + stepSize*index) + ', ' + (initUnselected + stepSize*index) + ', 1)';
                index += increment;
                if(index == unselectedSteps || index == 0)
                    increment *= -1;
            }
        })        
        
        index = 0;
        increment = 1;
        [].forEach.call(selectedFiles, function(elt){
            if(elt.className != 'fileHidden'){
                elt.style.backgroundColor = 'rgba(' + (initSelectedRed + stepSize*index) + ', ' + (initSelectedGreen + stepSize*index) + ', ' + (initSelectedBlue + stepSize*index) + ', 1)';
                index += increment;
                if(index == selectedSteps || index == 0)
                    increment *= -1;            
            }
        })

    }
