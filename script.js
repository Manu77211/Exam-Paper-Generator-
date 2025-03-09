// Function to navigate to a new page for Upload Paper
function navigateToUpload() {
    window.location.href= "upload.html"  ; // Redirects to the upload page
}

// Function to navigate to a new page for Add Question
function navigateToAdd() {
    window.location.href = "add.html"; // Redirects to the add question page
}

// Function to handle Remove Question directly on the same page
function removeQuestion() {
    const questionToRemove = document.getElementById("remove-input").value;
    if (questionToRemove.trim() === "") {
        alert("Please enter a question to remove.");
        return;
    }
    // Placeholder: Logic to send the question to backend for removal
    alert(`Question "${questionToRemove}" has been removed (Placeholder).`);
    document.getElementById("remove-input").value = ""; // Clear input field
}

// Function to navigate to Generate Question page
function navigateToGenerate() {
    window.location.href = "generate.html"; // Redirects to the generate page
}


function generatePaper() {
    // Get the number of questions for each difficulty
    let easy = document.getElementById('easy').value;
    let medium = document.getElementById('medium').value;
    let hard = document.getElementById('hard').value;

    // Validate input (ensure it's a non-negative integer)
    if (easy < 0 || medium < 0 || hard < 0) {
        alert("Please enter valid numbers (non-negative) for each category.");
        return;
    }

    // Display the generated paper (This is just a placeholder)
    let output = "<h2>Generated Question Paper</h2><ul>";
    
    // Generate questions based on the entered number
    for (let i = 0; i < easy; i++) {
        output += `<li>Easy Question ${i + 1}</li>`;
    }
    
    for (let i = 0; i < medium; i++) {
        output += `<li>Medium Question ${i + 1}</li>`;
    }
    
    for (let i = 0; i < hard; i++) {
        output += `<li>Hard Question ${i + 1}</li>`;
    }
    
    output += "</ul>";
    
    // Display the generated question paper
    document.getElementById("generated-paper").innerHTML = output;
}


function generatePaper() {
    var easyCount = document.getElementById("easy").value;
    var mediumCount = document.getElementById("medium").value;
    var hardCount = document.getElementById("hard").value;
    
    // Simulate fetching questions from the server or backend (this is a mock-up)
    var generatedQuestions = [];

    // Mock data (you will replace this with actual logic to get questions from your backend)
    var allQuestions = [
        { id: 1, text: "Easy Question 1", difficulty: "easy" },
        { id: 2, text: "Easy Question 2", difficulty: "easy" },
        { id: 3, text: "Medium Question 1", difficulty: "medium" },
        { id: 4, text: "Medium Question 2", difficulty: "medium" },
        { id: 5, text: "Hard Question 1", difficulty: "hard" },
        { id: 6, text: "Hard Question 2", difficulty: "hard" },
        // Add more mock questions here as needed
    ];

    // Filter questions based on the selected difficulty
    var easyQuestions = allQuestions.filter(q => q.difficulty === "easy").slice(0, easyCount);
    var mediumQuestions = allQuestions.filter(q => q.difficulty === "medium").slice(0, mediumCount);
    var hardQuestions = allQuestions.filter(q => q.difficulty === "hard").slice(0, hardCount);

    // Combine all selected questions
    generatedQuestions = [...easyQuestions, ...mediumQuestions, ...hardQuestions];

    // Display the generated questions
    var outputDiv = document.getElementById("generated-paper");
    outputDiv.innerHTML = "<h2>Generated Paper</h2>";
    
    if (generatedQuestions.length > 0) {
        generatedQuestions.forEach(function (question) {
            outputDiv.innerHTML += `<p><strong>Question ID: ${question.id}</strong><br>${question.text}</p>`;
        });
    } else {
        outputDiv.innerHTML += "<p>No questions generated based on the selected difficulty.</p>";
    }
}
