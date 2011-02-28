class CreateAttachments < ActiveRecord::Migration
  def self.up
    create_table :attachments do |t|
      t.integer :project_id
      t.string  :description

      # for acts_as_attachment
      t.string  :content_type
      t.string  :filename
      t.integer :size
      #t.integer :parent_id
      #t.string  :thumbnail

      # acts_as_list
      t.integer :position

      t.timestamps
    end
  end

  def self.down
    drop_table :attachments
  end
end
