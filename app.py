from flask import Flask, send_file, request, redirect, jsonify



import os  # Import to check for the file's existence

QUESTIONS_FILE = "questions.txt"

# Ensure the file exists
if not os.path.exists(QUESTIONS_FILE):
    with open(QUESTIONS_FILE, "w") as file:
        pass  # Create an empty file

app = Flask(__name__)

@app.route("/test")
def test():
    return "Server is working!"


@app.route("/")
def home():
    return send_file("index.html")  # Serve the main page

@app.route("/styles.css")
def styles():
    return send_file("styles.css")  # Serve the CSS

@app.route("/script.js")
def script():
    return send_file("script.js")  # Serve the JavaScript

@app.route("/upload.html")
def upload_page():
    return send_file("upload.html")  # Serve the upload page

@app.route("/add-question.html")
def add_question_page():
    return send_file("add-question.html")  # Serve the Add Question page

@app.route("/generate-paper.html")
def generate():
    return send_file("generate-paper.html")  # Serve the Generate Paper page

# New route to handle question uploads
@app.route("/upload", methods=["POST"])
def handle_upload():
    questions = request.form.get("questions")
    if questions:
        with open("questions.txt", "a") as file:  # 'a' appends to the file
            file.write(questions + "\n")
        return "Questions uploaded successfully!"
    return "No questions provided!", 400

# Route to handle adding a question


@app.route("/add-question", methods=["POST"])
def add_question():
    question_text = request.form.get("question-text")

    if not question_text:
        return "Please enter a question!", 400

    with open(QUESTIONS_FILE, "a") as file:
        file.write(question_text + "\n")

    return "Question added successfully!", 200



@app.route("/questions.txt")
def serve_questions_file():
    # Serve the file with no caching headers
    response = send_file("questions.txt")
    response.headers["Cache-Control"] = "no-store"
    return response

#for remove function

@app.route("/remove-question", methods=["POST"])
def remove_question():
    try:
        data = request.get_json()  # Get JSON data from the request
        question_id = data.get("id")  # Extract the question ID
        print(f"Received ID: {question_id}")  # Debugging line
        
        if not question_id:
            return jsonify({"error": "No question ID provided."}), 400

        # Read the questions from the file
        with open(QUESTIONS_FILE, "r") as file:
            questions = file.readlines()

        # Find and remove the question with the given ID
        question_found = False
        with open(QUESTIONS_FILE, "w") as file:
            for question in questions:
                # Assuming ID is at the start of each line like "1: Question"
                if question.startswith(f"{question_id}:"):
                    print(f"Removing question with ID {question_id}")  # Debugging line
                    question_found = True
                    continue  # Skip this question (delete it)
                file.write(question)  # Write back the other questions

        if question_found:
            return jsonify({"message": f"Question ID {question_id} removed successfully."})
        else:
            return jsonify({"error": "Question ID not found."}), 404

    except Exception as e:
        print(f"Error occurred: {str(e)}")
        return jsonify({"error": "An unexpected error occurred."}), 500


# to generate the questions 


import random  # Import random for shuffling

@app.route("/get-questions", methods=["GET"])
def get_questions():
    difficulty = request.args.get("difficulty")  # Get difficulty from query parameter
    if not difficulty:
        return jsonify({"error": "Difficulty not specified!"}), 400

    questions = []
    try:
        with open(QUESTIONS_FILE, "r") as file:
            for line in file:
                if f"Difficulty: {difficulty}" in line:
                    questions.append(line.strip())
    except FileNotFoundError:
        return jsonify({"error": "Questions file not found!"}), 500

    if not questions:
        return jsonify({"message": "No questions found for the specified difficulty!"}), 404

    # Shuffle the questions to randomize their order
    random.shuffle(questions)

    return jsonify({"questions": questions})



if __name__ == "__main__":
    app.run(debug=True)
