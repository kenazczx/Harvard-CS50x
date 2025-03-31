CREATE TABLE IF NOT EXISTS stocks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    stock TEXT NOT NULL,
    shares REAL NOT NULL,
    bought_price REAL NOT NULL,
    purchase_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

SELECT stock, shares FROM stocks GROUP BY user_id;

CREATE TABLE IF NOT EXISTS history (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    stock TEXT NOT NULL,
    shares REAL NOT NULL,
    price REAL NOT NULL,
    transaction_type TEXT NOT NULL,
    transaction_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id)
);


