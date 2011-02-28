# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20110227204357) do

  create_table "designs", :force => true do |t|
    t.string   "title"
    t.string   "address"
    t.text     "description"
    t.string   "photo_content_type"
    t.string   "photo_file_name"
    t.integer  "photo_file_size"
    t.integer  "width"
    t.integer  "height"
    t.integer  "position"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.datetime "photo_update_at"
  end

  create_table "project_files", :force => true do |t|
    t.integer  "project_id"
    t.string   "description"
    t.string   "attachment_content_type"
    t.string   "attachment_file_name"
    t.integer  "attachment_file_size"
    t.integer  "position"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.datetime "attachment_updated_at"
  end

  create_table "projects", :force => true do |t|
    t.string   "name"
    t.text     "brief"
    t.text     "description"
    t.integer  "position"
    t.string   "icon_content_type"
    t.string   "icon_file_name"
    t.integer  "icon_file_size"
    t.integer  "parent_id"
    t.string   "thumbnail"
    t.integer  "width"
    t.integer  "height"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.datetime "icon_updated_at"
  end

  create_table "roles", :force => true do |t|
    t.string "title"
  end

  create_table "roles_users", :id => false, :force => true do |t|
    t.integer "role_id"
    t.integer "user_id"
  end

  create_table "updates", :force => true do |t|
    t.string   "subject"
    t.text     "body"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "users", :force => true do |t|
    t.string   "login"
    t.string   "name"
    t.string   "crypted_password"
    t.string   "salt"
    t.datetime "created_at"
    t.datetime "updated_at"
    t.string   "password_salt"
    t.string   "persistence_token"
  end

end
