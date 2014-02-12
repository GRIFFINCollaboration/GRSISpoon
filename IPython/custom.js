$([IPython.events]).on('app_initialized.NotebookApp', function(){
    console.log('Hello from app_initialized.NotebookApp!')
});

$([IPython.events]).on('notebook_loaded.Notebook', function(){

    console.log('Hello from notebook_loaded.Notebook!');

    //failed JS loading attmepts :/
    //$.getScript('/static/custom/util.js' );
    //load_ext('util');

    require(['custom/util'], function(custom){
        window.selected = custom.selected;
        window.drawImg = custom.drawImg;
        window.exec_code = custom.exec_code;
        window.registerLeafList = custom.registerLeafList;
        window.getListOfVariables = custom.getListOfVariables;

	//silly but proves this is an async problem:
        window.setTimeout(getListOfVariables, 10000);
    } );

});

$([IPython.events]).on('status_started.Kernel', function(){
    console.log('Hello from status_started.Kernel!')
});
