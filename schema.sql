-- ===========================================================
-- 🚗 Random Vehicle Number Generator Database
-- ===========================================================

-- 1. Create database
CREATE DATABASE IF NOT EXISTS vehicle_registry
  CHARACTER SET utf8mb4
  COLLATE utf8mb4_unicode_ci;
USE vehicle_registry;

-- ===========================================================
-- 2. Users Table (for premium registration / ownership)
-- ===========================================================
CREATE TABLE IF NOT EXISTS users (
  id INT AUTO_INCREMENT PRIMARY KEY,
  username VARCHAR(100) NOT NULL UNIQUE,
  email VARCHAR(150) NOT NULL UNIQUE,
  password_hash VARCHAR(255) NOT NULL,
  is_premium TINYINT(1) NOT NULL DEFAULT 0,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB;

-- ===========================================================
-- 3. Cities Table
-- ===========================================================
CREATE TABLE IF NOT EXISTS cities (
  id INT AUTO_INCREMENT PRIMARY KEY,
  code CHAR(3) NOT NULL UNIQUE,
  name VARCHAR(100) NOT NULL
) ENGINE=InnoDB;

-- ===========================================================
-- 4. Vehicle Numbers Table
-- ===========================================================
CREATE TABLE IF NOT EXISTS vehicle_numbers (
  id BIGINT AUTO_INCREMENT PRIMARY KEY,
  city_id INT NOT NULL,
  year_small CHAR(2) NOT NULL,
  full_year INT NOT NULL,
  number CHAR(9) NOT NULL,
  is_premium TINYINT(1) NOT NULL DEFAULT 0,
  reserved_by INT DEFAULT NULL,
  created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,

  UNIQUE KEY uk_vehicle_number (number),
  KEY idx_city_year (city_id, full_year),

  CONSTRAINT fk_city FOREIGN KEY (city_id) REFERENCES cities(id)
    ON DELETE RESTRICT ON UPDATE CASCADE,
    
  CONSTRAINT fk_user FOREIGN KEY (reserved_by) REFERENCES users(id)
    ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB;

-- ===========================================================
-- 5. Premium Reservation History
-- ===========================================================
CREATE TABLE IF NOT EXISTS premium_reservations (
  id BIGINT AUTO_INCREMENT PRIMARY KEY,
  vehicle_id BIGINT NOT NULL,
  user_id INT NOT NULL,
  reserved_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,

  CONSTRAINT fk_vehicle FOREIGN KEY (vehicle_id)
    REFERENCES vehicle_numbers(id)
    ON DELETE CASCADE ON UPDATE CASCADE,
    
  CONSTRAINT fk_res_user FOREIGN KEY (user_id)
    REFERENCES users(id)
    ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB;

-- ===========================================================
-- 6. Seed Sample Cities
-- ===========================================================
INSERT IGNORE INTO cities (code, name) VALUES
('DEL', 'Delhi'),
('NYC', 'New York City'),
('BLR', 'Bengaluru'),
('MUM', 'Mumbai'),
('LDN', 'London'),
('DXB', 'Dubai');

-- ===========================================================
-- 7. Seed Sample Users
-- ===========================================================
INSERT IGNORE INTO users (username, email, password_hash, is_premium) VALUES
('admin', 'admin@example.com', '1234', 1),
('john_doe', 'john@example.com', 'hashed_password_here', 0),
('jane_doe', 'jane@example.com', 'hashed_password_here', 1);

-- ===========================================================
-- ✅ Ready to use
-- - Users table for accounts & premium flags
-- - Cities table for vehicle codes
-- - Vehicle numbers with uniqueness enforced
-- - Premium reservation logs
-- ===========================================================
