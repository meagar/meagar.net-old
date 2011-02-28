class AddRolesUsers < ActiveRecord::Migration
  def self.up
    create_table :roles_users, :id => false, :force => true do |t|
      t.integer :role_id
      t.integer :user_id
    end

    # Create our admin role
    u = User.new
    u.login    = 'meagar'
    u.password = 'password'
    u.name     = 'meagar'
    u.roles << Role.find_by_title('admin')
    u.save
  end

  def self.down
    drop_table 'roles_users'
  end
end
