<?php

/**
 * @file
 * Grid Plate type editing UI.
 */

/**
 * UI controller.
 */
class GridPlateTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Grid Plate entity types, including adding and removing fields and the display of fields.';

    return $items;
  }
}

/**
 * Generates the Grid Plate type editing form.
 */
function grid_plate_type_form($form, &$form_state, $grid_plate_type, $op = 'edit') {
  if ($op == 'clone') {
    $grid_plate_type->label .= ' (cloned)';
    $grid_plate_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $grid_plate_type->label,
    '#description' => t('The human-readable name of this Grid Plate type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($grid_plate_type->type) ? $grid_plate_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'grid_plate_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Grid Plate type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Grid Plate type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function grid_plate_type_form_submit(&$form, &$form_state) {
  $grid_plate_type = entity_ui_form_submit_build_entity($form, $form_state);
  $grid_plate_type->save();
  $form_state['redirect'] = 'admin/structure/grid_plate_types';
}

/**
 * Form API submit callback for the delete button.
 */
function grid_plate_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/grid_plate_types/manage/' . $form_state['grid_plate_type']->type . '/delete';
}
