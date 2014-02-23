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
        window.footerImage = custom.footerImage;

        //hide guts:
        document.getElementById('hideGuts').onclick();

	//TODO: really awful, figure out proper callback:
        window.setTimeout(function(){
            //branding
            //GRSISpoon('GRSIlogo', 20);
            footerImage('GRSIlogo', 2, '#DDDDDD');

	    //populate form options
            getListOfVariables();

            //start system monitor
            mpstatJS();
            window.systemLoadMonitorLoop = window.setInterval(mpstatJS, 5000);

            //use the end_space as a footer, write some stuff there:
            var footer = document.querySelector('.end_space'),
                footerTableHTML;

            footerTableHTML = "<div class='textBlock'><h3>Built in Vancouver by the GRIFFIN Collaboration</h3>"
            footerTableHTML += "<p>Code available on <a href='https://github.com/GRIFFINCollaboration/GRSISpoon'>Github</a><br>"
            footerTableHTML += "Web interface powered by the <a href='http://ipython.org/notebook.html'>ipython notebook</a><br>"
            footerTableHTML += "Copyright &#169 2014 GRIFFIN Collaboration<br>"
            footerTableHTML += "All code freely available under MIT license.</p>"
            footerTableHTML += "<table><tr><td><a class='imgLink' href='https://github.com/GRIFFINCollaboration/GRSISpoon'><img width='55' height='55' src='static/custom/GitHub-Mark-Light-64px.png'></img></a></td>"
            footerTableHTML += "<td><a class='imgLink' href='http://ipython.org/notebook.html'><img width='113' height='40' src='static/custom/ipyLogo.png'></img></a></td>"
            footerTableHTML += "<td><a class='imgLink' href='http://trshare.triumf.ca/~garns/GRIFFIN/'><img width='65' height='50' src='static/custom/GRIFFIN_Logo_White_small.png'></img></a></td></tr></table></div>"

            footerTableHTML += "<canvas id='footerImage' width='550' height='300'></canvas>";

            footer.innerHTML = footerTableHTML;

            footerImage('footerImage', 2, '#444444');

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
