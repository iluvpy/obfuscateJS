function coinFlip() {
    return Math.random() > .5 ? "Heads" : "Tails"; 
}

function printHello() {
    console.log("printHello");
}

function main() {
    var coinFlips = [];
    for (var i = 0; i < 100; i++) {
        coinFlips.push(coinFlip());
    }

    var heads = 0;
    var tails = 0;
    for (var coinflip of coinFlips) {
        if (coinflip == "Heads") heads++;
        else tails++;
    }

    console.log(heads);
    console.log(tails);

}

main();