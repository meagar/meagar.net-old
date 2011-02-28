class CreateDesigns < ActiveRecord::Migration
  def self.up
    create_table :designs do |t|
      t.string :title
      t.string :address
      t.text :description

      # for attachment_fu
      t.string  :content_type
      t.string  :filename
      t.integer :size
      t.integer :width
      t.integer :height

      # for acts_as_list
      t.integer :position
      
      t.timestamps
    end
  end

  def self.down
    drop_table :designs
  end
end
