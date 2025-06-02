CREATE TABLE IF NOT EXISTS role(
    id SERIAL PRIMARY KEY,
    roles VARCHAR(10) UNIQUE
    );
INSERT INTO role (roles) VALUES ('subscriber'),('user'),('guest') ON CONFLICT DO NOTHING;

CREATE TABLE IF NOT EXISTS users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(20) UNIQUE NOT NULL,
    password TEXT NOT NULL,
    user_role INTEGER REFERENCES role(id),
    valid_until DATE,
    email TEXT
    );

CREATE TABLE IF NOT EXISTS license(
    id SERIAL PRIMARY KEY,
    license VARCHAR(255) UNIQUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    issued_to INTEGER REFERENCES users(id),
    is_active BOOLEAN DEFAULT TRUE
    );