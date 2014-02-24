    function hide(){
        $('div.input').hide();
        $('div.out_prompt_overlay.prompt').hide();
        $('div.prompt.output_prompt').hide();
        $('div#header').hide();
        $('div#menubar-container').hide();
        //$('div#pager').hide();
        $('button#hideGuts').hide();
        $('div#showGuts').show();
    }

    function show(){
        $('div.input').show();
        $('div.out_prompt_overlay.prompt').show();
        $('div.prompt.output_prompt').show();
        $('div#header').show();
        $('div#menubar-container').show();
        //$('div#pager').show();
        $('button#hideGuts').show();
        $('div#showGuts').hide();
    }
