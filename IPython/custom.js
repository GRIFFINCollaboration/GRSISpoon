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
        window.GRSISpoon = custom.GRSISpoon;
        window.constructHexColor = custom.constructHexColor;
        window.scalepickr = custom.scalepickr;
        window.mpstatJS = custom.mpstatJS;
        window.illustrateMpstat = custom.illustrateMpstat;

        //hide guts:
        document.getElementById('hideGuts').onclick();

	//TODO: really awful, figure out proper callback:
        window.setTimeout(function(){
            //branding
            GRSISpoon('GRSIlogo', 20);

	    //populate form options
            getListOfVariables();

            //start system monitor
            mpstatJS();
            window.systemLoadMonitorLoop = window.setInterval(mpstatJS, 5000);

            //use the end_space as a footer, write some stuff there:
            document.querySelector('.end_space').innerHTML = 'GRSISpoon Developed by the GRIFFIN Collaboration - fork us on <a href="https://github.com/GRIFFINCollaboration/GRSISpoon">Github</a> - powered by the <a href="http://ipython.org/notebook.html">IPython Notebook</a>'

            //fade everything in after setup
            document.getElementById('notebook').style.opacity = 1;
        }, 500);
 
    } );

    //console logs all the custom events available :)
    //console.log($._data($([IPython.events])[0], "events" ));

});

$([IPython.events]).on('status_started.Kernel', function(){
    console.log('Hello from status_started.Kernel!')
});
