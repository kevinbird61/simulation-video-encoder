const docogen = require('docogen'),
    path = require('path');

docogen.generate_latexpdf(path.join(__dirname,'..'),__dirname,{output: "simulation-report"},
    (err,msg) => {
        console.log(msg)
    })