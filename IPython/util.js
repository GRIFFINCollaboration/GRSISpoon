define(function(){
    
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

    return {
        selected : selected,
        drawImg : drawImg,
        exec_code : exec_code,
        registerLeafList : registerLeafList,
        getListOfVariables : getListOfVariables
    }
});
