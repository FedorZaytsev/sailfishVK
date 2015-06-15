

function log(){
    if(console){
        console.log.apply(console, arguments);
    }
}
