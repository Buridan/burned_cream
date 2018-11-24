 //Mini Jeu du PlusOuMoins
if (confirm("tu veux jouer avec moi?"))
{
var jouer= true;
while(jouer)
{
var nbr1 ;
var nbr2 = prompt("psst... c'est quoi le nombre mystère?");

while(nbr1 != nbr2)
	{
	nbr1 = prompt("c'est quoi le nombre mystère?");
	if (nbr1>nbr2)
		{
		alert("C'est plus petit!");
                }
	else if(nbr1 < nbr2)
        	{
		alert("C'est plus grand!");
		}
	else
        	{
		alert("Bravo! Tu as découvert le nombre mystère!")
		}
	}
jouer= confirm("Veux-tu rejouer?");
}
}
else{
alert("Dommage, j'avais des bonbons...");}
/*
var chiffre= new Array ();
var i=0, c;
do
{
chiffre[i] =prompt ("Entrez vos nombres?");
//if(isNaN(chiffre[i]){ i--;}
if(chiffre[i]){
c=i;}
alert(i+c);
alert(chiffre.length);
i++;
}
while(c<=chiffre.length);

alert(isNaN(i));
/*
var fct = prompt ("quel fonction appliquer? add|sous|mult|div|moy|mod");

var operation = new Array();
	operation["add"] = function(chfr1,chfr2, chiffre.length)
    {	for (chiffre.length<=i,i=0,i++)

    	return chfr1+chfr2; };
	operation["sous"] = function(chfr1,chfr2){ return chfr1-chfr2; };
	operation["mult"] = function(chfr1,chfr2){ return chfr1*chfr2; };
	operation["div"] = function(chfr1,chfr2){ return chfr1/chfr2; };
	operation["moy"] = function(chfr1,chfr2){ return (chfr1+chfr2)/2; };
	operation["mod"] = function(chfr1,chfr2){ return chfr1%chfr2; };

var resultat = operation[fct](chfr1,chfr2);
alert("le resultat est: " + resultat);*/