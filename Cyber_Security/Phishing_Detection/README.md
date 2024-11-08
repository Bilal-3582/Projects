### Phishing Email Detection Model Using LSTM

In this project, an LSTM (Long Short-Term Memory) model was implemented to detect phishing emails from a dataset titled `Phishing_Email.csv`, which was sourced from Kaggle. The main steps in the process include data loading, preprocessing, model building, training, and evaluation, which are summarized below:

[Phishing_Email.csv](https://www.kaggle.com/datasets/subhajournal/phishingemails)

1. **Data Loading and Preprocessing**:
   - The CSV file `Phishing_Email.csv` was loaded, containing two columns: "Email Text" (the content of the email) and "Email Type" (either "Safe Email" or "Phishing Email").
   - The dataset was cleaned by dropping rows where the "Email Text" column had missing values.
   - The "Email Type" column was transformed into numerical labels (`0` for Safe Email, `1` for Phishing Email) for binary classification.

2. **Text Vectorization**:
   - The `TfidfVectorizer` was applied to convert the text data into numerical features, capturing the importance of words in each email. The number of features was limited to 5000 to avoid overfitting and to reduce computation time.
   - The resulting text vectors were reshaped to 3D arrays to be compatible with the LSTM model, where each email is treated as a single timestep with 5000 features.

3. **Model Architecture**:
   - A Sequential model was built with the following layers:
     - **LSTM Layer**: The core of the model, consisting of 128 units, with 50% dropout and 50% recurrent dropout to prevent overfitting.
     - **Dense Layer**: A fully connected layer with 64 units and ReLU activation function.
     - **Output Layer**: A single unit with a sigmoid activation function to output a probability for binary classification.
   - The model was compiled using the Adam optimizer, binary cross-entropy loss function, and accuracy as the evaluation metric.

4. **Model Training**:
   - The model was trained for 5 epochs using a batch size of 64. The training dataset was split into 80% training and 20% testing data, and validation was performed on the test set during training.

5. **Model Evaluation**:
   - After training, the model was evaluated on the test set. The test accuracy was calculated and printed as the final performance metric. The result was approximately **test accuracy** of 90% (based on the test printout).

6. **Visualization**:
   - A pie chart was generated to visualize the distribution of the test results, showing the proportion of correctly and incorrectly classified emails. The chart used two colors to distinguish between correctly classified (green) and incorrectly classified (red) emails.

### Key Points:
- **Data preprocessing** included text vectorization with TF-IDF and reshaping for LSTM input.
- **LSTM model** was used to capture sequential patterns in the email text for classification.
- **Model achieved high accuracy** in identifying phishing emails, demonstrating the effectiveness of LSTM for text-based classification tasks.
- **Visualization** helped in understanding the performance of the model on the test dataset.

This approach shows that LSTM models, commonly used for sequential data, can be quite effective in text classification tasks like phishing email detection.

### Furute Works:
For future work, the phishing email detection system can be integrated with Wazuh, an open-source security monitoring platform, to enhance real-time detection and response capabilities. Wazuh can be used to monitor system logs, network traffic, and other security-related events in real time, providing a more comprehensive approach to cybersecurity by automating the detection of phishing emails and malicious activity.
