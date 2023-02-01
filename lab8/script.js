const buttons = document.querySelectorAll(".answer");
    buttons.forEach(function(button)
    {
        button.addEventListener("click",function(){
            if ((button.id == "answer3" || button.id == "answer4"))
            {
                button.style.backgroundColor = "#509650";
                result1.innerHTML = "Correct!";
                result1.style.color = "#509650";
            }
            else
            {
                button.style.backgroundColor= "#dd5050";
                result1.innerHTML= "Icorrect";
                result1.style.color = "#dd5050";

            }
            buttons.forEach(function(button){
                    button.disabled = true;
                })
        });
    });
const confirmer = document.getElementById("confirm");
confirmer.addEventListener("click", function(input
)
{
    const answer = document.getElementById("answer5").value;
    if (answer.toUpperCase() === "MONACO"){
        result2.innerHTML= "Correct!";
        result2.style.color = "#509650";
        answer5.style.backgroundColor = "#509650";
    }
    else{
        result2.innerHTML= "Wrong";
        result2.style.color = "#dd5050"
        answer5.style.backgroundColor = "#dd5050";
    }
    answer5.style.color = "#ffff"
});