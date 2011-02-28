class CreateProjects < ActiveRecord::Migration
  def self.up
    create_table :projects do |t|
      t.string  :name
      t.text    :brief
      t.text    :description

      # for acts_as_list
      t.integer :position

      # for attachment_fu
      t.string  :content_type
      t.string  :filename
      t.integer :size
      t.integer :parent_id
      t.string  :thumbnail
      t.integer :width
      t.integer :height

      t.timestamps
    end
  end

  def self.down
    drop_table :projects
  end
end
