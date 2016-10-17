"use strict";

$( document ).ready( function() {

    var textbox = $( "#text" );

    textbox.change( function() {
        var language = $( "#rules" ).val();
        textbox.val( doReplacements( textbox.val(), language ) );
    } );

    textbox.keypress( function( event ) {
        if ( event.keyCode == 13 || event.key == ' ') {
            var language = $( "#rules" ).val();
            textbox.val( doReplacements( textbox.val(), language ) );
        }
    } );

} );

function doReplacements( text, language ) {

    var openingDouble = quotationRules[ language ].double.opening;
    var closingDouble = quotationRules[ language ].double.closing;

    // double quotes
    text = text.replace( /(\s+)"/g, "$1" + openingDouble );
    text = text.replace( /^"/g, openingDouble );
    text = text.replace( /"/g, closingDouble );

    var openingSingle = quotationRules[ language ].single.opening;
    var closingSingle = quotationRules[ language ].single.closing;

    // '80s -> ’80s
    text = text.replace( /'(\d{2}s)/g, "’$1" );

    // "rock 'n' roll" -> "rock ’n’ roll"
    text = text.replace( /(\w+\s+)'(\w{1})'/g, "$1’$2’" );

    // "don't" -> "don’t"
    text = text.replace( /(\w)'(\w)/g, "$1’$2" );

    // single quotes
    text = text.replace( /(\s+)'/g, "$1" + openingSingle );
    text = text.replace( /^'/g, openingSingle );
    text = text.replace( new RegExp( openingDouble + "'" ), openingDouble + openingSingle );
    text = text.replace( /'/g, closingSingle );

    // ... -> …
    text = text.replace( /\.\.\./g, "…" );

    // -- -> –
    text = text.replace( /--/g, "–" );

    return text;
}


var quotationRules = {
    "en" : {
        double : {
            opening : "“",
            closing : "”"
        },
        single : {
            opening : "‘",
            closing : "’"
        }
    },
    "de" : {
        double : {
            opening : "„",
            closing : "“"
        },
        single : {
            opening : "‚",
            closing : "‘"
        }
    },
    "de_book" : {
        double : {
            opening : "»",
            closing : "«"
        },
        single : {
            opening : "›",
            closing : "‹"
        }
    },
    "fr" : {
        double : {
            opening : "« ",
            closing : " »"
        },
        single : {
            opening : "‹ ",
            closing : " ›"
        }
    }
};
