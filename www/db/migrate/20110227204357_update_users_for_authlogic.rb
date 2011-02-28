class UpdateUsersForAuthlogic < ActiveRecord::Migration
  def self.up
		rename_column :users, :pwhash, :crypted_password
		add_column :users, :password_salt, :string
		add_column :users, :persistence_token, :string
  end

  def self.down
		drop_column :users, :password_salt
		drop_column :users, :persistence_token
		rename_column :users, :crypted_password, :pwhash
  end
end
